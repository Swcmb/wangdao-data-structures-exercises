#include<stdio.h>
#define MaxSize 10

typedef int ElemType;

typedef struct{
    ElemType data[MaxSize];
    int top;
}SqStack;

// 初始化栈
void InitStack(SqStack &S){
    S.top = -1;
}

// 判断栈是否为空
bool StackEmpty(SqStack S){
    if(S.top == -1)
        return true;
    else
        return false;
}

// 入栈
bool Push(SqStack &S, ElemType x){
    if(S.top == MaxSize - 1)
        return false;
    S.data[++S.top] = x;
    return true;
}

// 出栈
bool Pop(SqStack &S, ElemType &x){
    if(S.top == -1)
        return false;
    x = S.data[S.top--];
    return true;
}

// 读取栈顶元素
bool GetTop(SqStack S, ElemType &x){
    if(S.top == -1)
        return false;
    x = S.data[S.top];
    return true;
}

// 打印栈
void PrintStack(SqStack S){
    for(int i=S.top; i>=0; i--){
        printf("%d ", S.data[i]);
    }
    printf("\n");
}

// 共享栈
typedef struct{
    ElemType data[MaxSize];
    int top0;
    int top1;
}ShStack;

// 初始化共享栈
void InitShStack(ShStack &S){
    S.top0 = -1;
    S.top1 = MaxSize;
}

// 0号栈入栈
bool Push0(ShStack &S, ElemType x){
    if(S.top0 + 1 == S.top1)
        return false;
    S.data[++S.top0] = x;
    return true;
}

// 1号栈入栈
bool Push1(ShStack &S, ElemType x){
    if(S.top0 + 1 == S.top1)
        return false;
    S.data[--S.top1] = x;
    return true;
}

// 0号栈出栈
bool Pop0(ShStack &S, ElemType &x){
    if(S.top0 == -1)
        return false;
    x = S.data[S.top0--];
    return true;
}

// 1号栈出栈
bool Pop1(ShStack &S, ElemType &x){
    if(S.top1 == MaxSize)
        return false;
    x = S.data[S.top1++];
    return true;
}

int main(){
    // 测试顺序栈
    printf("=== 顺序栈 ===\n");
    SqStack S;
    InitStack(S);
    
    Push(S, 10);
    Push(S, 20);
    Push(S, 30);
    printf("栈元素：");
    PrintStack(S);
    
    int x;
    Pop(S, x);
    printf("出栈元素：%d\n", x);
    printf("栈元素：");
    PrintStack(S);
    
    GetTop(S, x);
    printf("栈顶元素：%d\n", x);
    
    // 测试共享栈
    printf("\n=== 共享栈 ===\n");
    ShStack ShS;
    InitShStack(ShS);
    
    Push0(ShS, 100);
    Push0(ShS, 200);
    Push1(ShS, 300);
    Push1(ShS, 400);
    
    Pop0(ShS, x);
    printf("0号栈出栈：%d\n", x);
    
    Pop1(ShS, x);
    printf("1号栈出栈：%d\n", x);
    
    return 0;
}