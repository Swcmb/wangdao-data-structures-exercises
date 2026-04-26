#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct DNode{
    ElemType data;
    struct DNode *prior, *next;
}DNode, *DLinklist;

// 初始化双链表
bool InitDLinkList(DLinklist &L){
    L = (DNode *)malloc(sizeof(DNode));
    if(L==NULL)
        return false;
    L->prior = NULL;
    L->next = NULL;
    return true;
}

// 判断双链表是否为空
bool Empty(DLinklist L){
    if(L->next == NULL)
        return true;
    else
        return false;
}

// 后插操作
bool InsertNextDNode(DNode *p, DNode *s){
    if(p==NULL || s==NULL)
        return false;
    s->next = p->next;
    if(p->next != NULL)
        p->next->prior = s;
    s->prior = p;
    p->next = s;
    return true;
}

// 删除p节点的后继节点
bool DeletNextDNode(DNode *p){
    if(p==NULL) return false;
    DNode *q = p->next;
    if(q==NULL) return false;
    p->next = q->next;
    if(q->next != NULL)
        q->next->prior = p;
    free(q);
    return true;
}

// 销毁一个双链表
bool DestoryList(DLinklist &L){
    while(L->next != NULL){
        DeletNextDNode(L);
    }
    free(L);
    L=NULL;
    return true;
}

// 打印双链表
void PrintList(DLinklist L){
    DNode *p = L->next;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 前向遍历
void PrintListPrior(DLinklist L){
    DNode *p = L;
    while(p->next != NULL){
        p = p->next;
    }
    while(p != L){
        printf("%d ", p->data);
        p = p->prior;
    }
    printf("\n");
}

int main(){
    DLinklist L;
    InitDLinkList(L);
    
    // 插入元素
    DNode *s1 = (DNode *)malloc(sizeof(DNode));
    s1->data = 10;
    InsertNextDNode(L, s1);
    
    DNode *s2 = (DNode *)malloc(sizeof(DNode));
    s2->data = 20;
    InsertNextDNode(s1, s2);
    
    DNode *s3 = (DNode *)malloc(sizeof(DNode));
    s3->data = 30;
    InsertNextDNode(s2, s3);
    
    printf("双链表：");
    PrintList(L);
    
    // 测试删除
    DeletNextDNode(s1);
    printf("删除后：");
    PrintList(L);
    
    // 测试前向遍历
    printf("前向遍历：");
    PrintListPrior(L);
    
    // 销毁链表
    DestoryList(L);
    
    return 0;
}