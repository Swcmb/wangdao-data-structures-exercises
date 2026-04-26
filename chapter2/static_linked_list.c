#include<stdio.h>
#define MaxSize 10

typedef int ElemType;

typedef struct{
    ElemType data;
    int next;
}SLinkList[MaxSize];

// 初始化静态链表
void InitList(SLinkList &L){
    for(int i=0; i<MaxSize-1; i++){
        L[i].next = i+1;
    }
    L[MaxSize-1].next = 0; // 尾节点的next指向0
}

// 分配空闲节点
int Malloc_SL(SLinkList &L){
    int i = L[0].next;
    if(L[0].next != 0){
        L[0].next = L[i].next;
    }
    return i;
}

// 回收节点
void Free_SL(SLinkList &L, int k){
    L[k].next = L[0].next;
    L[0].next = k;
}

// 插入操作
void ListInsert(SLinkList &L, int i, ElemType e){
    int j = Malloc_SL(L);
    if(j){ // 分配成功
        L[j].data = e;
        int p = MaxSize-1;
        for(int l=1; l<i; l++){
            p = L[p].next;
        }
        L[j].next = L[p].next;
        L[p].next = j;
    }
}

// 删除操作
void ListDelete(SLinkList &L, int i, ElemType &e){
    int p = MaxSize-1;
    for(int l=1; l<i; l++){
        p = L[p].next;
    }
    int q = L[p].next;
    e = L[q].data;
    L[p].next = L[q].next;
    Free_SL(L, q);
}

// 打印静态链表
void PrintList(SLinkList L){
    int p = L[MaxSize-1].next;
    while(p != 0){
        printf("%d ", L[p].data);
        p = L[p].next;
    }
    printf("\n");
}

int main(){
    SLinkList L;
    InitList(L);
    
    // 插入元素
    ListInsert(L, 1, 10);
    ListInsert(L, 2, 20);
    ListInsert(L, 3, 30);
    printf("静态链表：");
    PrintList(L);
    
    // 删除元素
    int e;
    ListDelete(L, 2, e);
    printf("删除后：");
    PrintList(L);
    printf("删除的元素：%d\n", e);
    
    return 0;
}