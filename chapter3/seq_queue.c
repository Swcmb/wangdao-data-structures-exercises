#include<stdio.h>
#define MaxSize 10

typedef int ElemType;

typedef struct{
    ElemType data[MaxSize];
    int front, rear;
}SqQueue;

// 初始化队列
void InitQueue(SqQueue &Q){
    Q.rear = Q.front = 0;
}

// 判断队列是否为空
bool QueueEmpty(SqQueue Q){
    if(Q.rear == Q.front)
        return true;
    else
        return false;
}

// 入队
bool EnQueue(SqQueue &Q, ElemType x){
    if((Q.rear+1)%MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear+1)%MaxSize;
    return true;
}

// 出队
bool DeQueue(SqQueue &Q, ElemType &x){
    if(Q.rear == Q.front)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front+1)%MaxSize;
    return true;
}

// 获取队头元素
bool GetHead(SqQueue Q, ElemType &x){
    if(Q.rear == Q.front)
        return false;
    x = Q.data[Q.front];
    return true;
}

// 打印队列
void PrintQueue(SqQueue Q){
    int i = Q.front;
    while(i != Q.rear){
        printf("%d ", Q.data[i]);
        i = (i+1)%MaxSize;
    }
    printf("\n");
}

// 队列长度
int QueueLength(SqQueue Q){
    return (Q.rear - Q.front + MaxSize) % MaxSize;
}

// 带size的队列
typedef struct{
    ElemType data[MaxSize];
    int front, rear;
    int size;
}SqQueueWithSize;

// 初始化队列
void InitQueueWithSize(SqQueueWithSize &Q){
    Q.rear = Q.front = 0;
    Q.size = 0;
}

// 判断队列是否为空
bool QueueEmptyWithSize(SqQueueWithSize Q){
    if(Q.size == 0)
        return true;
    else
        return false;
}

// 入队
bool EnQueueWithSize(SqQueueWithSize &Q, ElemType x){
    if(Q.size == MaxSize)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear+1)%MaxSize;
    Q.size++;
    return true;
}

// 出队
bool DeQueueWithSize(SqQueueWithSize &Q, ElemType &x){
    if(Q.size == 0)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front+1)%MaxSize;
    Q.size--;
    return true;
}

int main(){
    // 测试循环队列
    printf("=== 循环队列 ===\n");
    SqQueue Q;
    InitQueue(Q);
    
    EnQueue(Q, 10);
    EnQueue(Q, 20);
    EnQueue(Q, 30);
    printf("队列元素：");
    PrintQueue(Q);
    printf("队列长度：%d\n", QueueLength(Q));
    
    int x;
    DeQueue(Q, x);
    printf("出队元素：%d\n", x);
    printf("队列元素：");
    PrintQueue(Q);
    
    GetHead(Q, x);
    printf("队头元素：%d\n", x);
    
    // 测试带size的队列
    printf("\n=== 带size的队列 ===\n");
    SqQueueWithSize QS;
    InitQueueWithSize(QS);
    
    EnQueueWithSize(QS, 100);
    EnQueueWithSize(QS, 200);
    EnQueueWithSize(QS, 300);
    
    DeQueueWithSize(QS, x);
    printf("出队元素：%d\n", x);
    
    return 0;
}