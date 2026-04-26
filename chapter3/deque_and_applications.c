#include<stdio.h>
#include<stdlib.h>
#define MaxSize 10

typedef int ElemType;

// 双端队列（顺序实现）
typedef struct{
    ElemType data[MaxSize];
    int front, rear;
}Deque;

// 初始化双端队列
void InitDeque(Deque &Q){
    Q.front = Q.rear = 0;
}

// 判断队列是否为空
bool DequeEmpty(Deque Q){
    return Q.front == Q.rear;
}

// 从队头入队
bool InsertFront(Deque &Q, ElemType x){
    if((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.front = (Q.front - 1 + MaxSize) % MaxSize;
    Q.data[Q.front] = x;
    return true;
}

// 从队尾入队
bool InsertRear(Deque &Q, ElemType x){
    if((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}

// 从队头出队
bool DeleteFront(Deque &Q, ElemType &x){
    if(Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}

// 从队尾出队
bool DeleteRear(Deque &Q, ElemType &x){
    if(Q.front == Q.rear)
        return false;
    Q.rear = (Q.rear - 1 + MaxSize) % MaxSize;
    x = Q.data[Q.rear];
    return true;
}

// 打印双端队列
void PrintDeque(Deque Q){
    int i = Q.front;
    while(i != Q.rear){
        printf("%d ", Q.data[i]);
        i = (i + 1) % MaxSize;
    }
    printf("\n");
}

// 栈的应用：括号匹配
typedef struct{
    char data[MaxSize];
    int top;
}SqStack;

void InitStack(SqStack &S){
    S.top = -1;
}

bool StackEmpty(SqStack S){
    return S.top == -1;
}

bool Push(SqStack &S, char x){
    if(S.top == MaxSize - 1)
        return false;
    S.data[++S.top] = x;
    return true;
}

bool Pop(SqStack &S, char &x){
    if(S.top == -1)
        return false;
    x = S.data[S.top--];
    return true;
}

// 判断括号是否匹配
bool bracketCheck(char str[], int length){
    SqStack S;
    InitStack(S);
    for(int i=0; i<length; i++){
        if(str[i] == '(' || str[i] == '[' || str[i] == '{'){
            Push(S, str[i]);
        }else{
            if(StackEmpty(S))
                return false;
            char topElem;
            Pop(S, topElem);
            if(str[i] == ')' && topElem != '(') return false;
            if(str[i] == ']' && topElem != '[') return false;
            if(str[i] == '}' && topElem != '{') return false;
        }
    }
    return StackEmpty(S);
}

int main(){
    // 测试双端队列
    printf("=== 双端队列 ===\n");
    Deque Q;
    InitDeque(Q);
    
    InsertFront(Q, 10);
    InsertRear(Q, 20);
    InsertFront(Q, 5);
    InsertRear(Q, 30);
    printf("双端队列元素：");
    PrintDeque(Q);
    
    int x;
    DeleteFront(Q, x);
    printf("从队头出队：%d\n", x);
    DeleteRear(Q, x);
    printf("从队尾出队：%d\n", x);
    printf("剩余元素：");
    PrintDeque(Q);
    
    // 测试括号匹配
    printf("\n=== 括号匹配 ===\n");
    char str1[] = "{[()]}";
    char str2[] = "{[(])}";
    char str3[] = "{{{{}}";
    
    printf("%s: %s\n", str1, bracketCheck(str1, 6) ? "匹配" : "不匹配");
    printf("%s: %s\n", str2, bracketCheck(str2, 6) ? "匹配" : "不匹配");
    printf("%s: %s\n", str3, bracketCheck(str3, 5) ? "匹配" : "不匹配");
    
    return 0;
}