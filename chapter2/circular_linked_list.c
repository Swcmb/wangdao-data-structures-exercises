#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, *Linklist;

// 初始化循环单链表
bool InitList(LinkList &L){
    L = (LNode *)malloc(sizeof(LNode));
    if(L==NULL)
        return false;
    L->next = L; //头结点next指针指向头结点
    return true;
}

// 判断循环单链表是否为空
bool Empty(LinkList L){
    if(L->next == L)
        return true;
    else
        return false;
}

// 判断结点p是否为循环单链表的表尾结点
bool isTail(LinkList L, LNode *p){
    if(p->next == L)
        return true;
    else
        return false;
}

// 插入操作
bool ListInsert(LinkList &L, int i, ElemType e){
    if(i<1) return false;
    LNode *p = L;
    int j=0;
    while(p!=NULL && j<i-1){
        p = p->next;
        j++;
        if(p == L) return false; // 防止无限循环
    }
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

// 打印循环单链表
void PrintList(LinkList L){
    if(Empty(L)) return;
    LNode *p = L->next;
    while(p != L){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 循环双链表
typedef struct DNode{
    ElemType data;
    struct DNode *prior, *next;
}DNode, *DLinklist;

// 初始化循环双链表
bool InitDLinkList(DLinklist &L){
    L = (DNode *)malloc(sizeof(DNode));
    if(L==NULL)
        return false;
    L->prior = L;
    L->next = L;
    return true;
}

// 判断循环双链表是否为空
bool Empty(DLinklist L){
    if(L->next == L)
        return true;
    else
        return false;
}

// 判断结点p是否为循环双链表的表尾结点
bool isTail(DLinklist L, DNode *p){
    if(p->next == L)
        return true;
    else
        return false;
}

// 插入操作
bool InsertNextDNode(DNode *p, DNode *s){
    s->next = p->next;
    p->next->prior = s;
    s->prior = p;
    p->next = s;
    return true;
}

// 删除操作
bool DeleteNextDNode(DNode *p){
    if(p==NULL) return false;
    DNode *q = p->next;
    if(q==NULL) return false;
    p->next = q->next;
    q->next->prior = p;
    free(q);
    return true;
}

// 打印循环双链表
void PrintDList(DLinklist L){
    if(Empty(L)) return;
    DNode *p = L->next;
    while(p != L){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main(){
    // 测试循环单链表
    printf("=== 循环单链表 ===\n");
    LinkList CL;
    InitList(CL);
    ListInsert(CL, 1, 10);
    ListInsert(CL, 2, 20);
    ListInsert(CL, 3, 30);
    PrintList(CL);
    
    // 测试循环双链表
    printf("\n=== 循环双链表 ===\n");
    DLinklist DCL;
    InitDLinkList(DCL);
    
    DNode *s1 = (DNode *)malloc(sizeof(DNode));
    s1->data = 100;
    InsertNextDNode(DCL, s1);
    
    DNode *s2 = (DNode *)malloc(sizeof(DNode));
    s2->data = 200;
    InsertNextDNode(s1, s2);
    
    DNode *s3 = (DNode *)malloc(sizeof(DNode));
    s3->data = 300;
    InsertNextDNode(s2, s3);
    
    PrintDList(DCL);
    
    return 0;
}