#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode;

typedef struct{
    LinkNode *front, *rear;
}LinkQueue;

// 初始化队列（带头结点）
void InitQueue(LinkQueue &Q){
    Q.front = Q.rear = (LinkNode *)malloc(sizeof(LinkNode));
    Q.front->next = NULL;
}

// 判断队列是否为空
bool IsEmpty(LinkQueue Q){
    if(Q.front == Q.rear)
        return true;
    else
        return false;
}

// 入队
void EnQueue(LinkQueue &Q, ElemType x){
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
}

// 出队
bool DeQueue(LinkQueue &Q, ElemType &x){
    if(Q.front == Q.rear)
        return false;
    LinkNode *p = Q.front->next;
    x = p->data;
    Q.front->next = p->next;
    if(Q.rear == p)
        Q.rear = Q.front;
    free(p);
    return true;
}

// 获取队头元素
bool GetHead(LinkQueue Q, ElemType &x){
    if(Q.front == Q.rear)
        return false;
    x = Q.front->next->data;
    return true;
}

// 打印队列
void PrintQueue(LinkQueue Q){
    LinkNode *p = Q.front->next;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 不带头结点的链队列
typedef struct{
    LinkNode *front, *rear;
}LinkQueueNoHead;

// 初始化队列（不带头结点）
void InitQueueNoHead(LinkQueueNoHead &Q){
    Q.front = NULL;
    Q.rear = NULL;
}

// 判断队列是否为空
bool IsEmptyNoHead(LinkQueueNoHead Q){
    if(Q.front == NULL)
        return true;
    else
        return false;
}

// 入队
void EnQueueNoHead(LinkQueueNoHead &Q, ElemType x){
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x;
    s->next = NULL;
    if(Q.front == NULL){
        Q.front = s;
        Q.rear = s;
    }else{
        Q.rear->next = s;
        Q.rear = s;
    }
}

// 出队
bool DeQueueNoHead(LinkQueueNoHead &Q, ElemType &x){
    if(Q.front == NULL)
        return false;
    LinkNode *s = Q.front;
    x = s->data;
    if(Q.front == Q.rear){
        Q.front = Q.rear = NULL;
    }else{
        Q.front = Q.front->next;
    }
    free(s);
    return true;
}

int main(){
    // 测试带头结点的链队列
    printf("=== 带头结点的链队列 ===\n");
    LinkQueue Q;
    InitQueue(Q);
    
    EnQueue(Q, 10);
    EnQueue(Q, 20);
    EnQueue(Q, 30);
    printf("队列元素：");
    PrintQueue(Q);
    
    int x;
    DeQueue(Q, x);
    printf("出队元素：%d\n", x);
    printf("队列元素：");
    PrintQueue(Q);
    
    GetHead(Q, x);
    printf("队头元素：%d\n", x);
    
    // 测试不带头结点的链队列
    printf("\n=== 不带头结点的链队列 ===\n");
    LinkQueueNoHead QNH;
    InitQueueNoHead(QNH);
    
    EnQueueNoHead(QNH, 100);
    EnQueueNoHead(QNH, 200);
    EnQueueNoHead(QNH, 300);
    
    DeQueueNoHead(QNH, x);
    printf("出队元素：%d\n", x);
    
    return 0;
}