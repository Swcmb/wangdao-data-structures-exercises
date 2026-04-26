#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct Linknode{
    ElemType data;
    struct Linknode *next;
}Linknode,*LiStack;

// 初始化栈
bool InitStack(LiStack &L){
    L = (Linknode *)malloc(sizeof(Linknode));
    if(L == NULL)
        return false;
    L->next = NULL;
    return true;
}

// 判断栈是否为空
bool isEmpty(LiStack L){
    if(L->next == NULL)
        return true;
    else
        return false;
}

// 入栈
bool pushStack(LiStack &L, ElemType x){
    Linknode *s = (Linknode *)malloc(sizeof(Linknode));
    if(s == NULL)
        return false;
    s->data = x;
    s->next = L->next;
    L->next = s;
    return true;
}

// 出栈
bool popStack(LiStack &L, ElemType &x){
    if(L->next == NULL)
        return false;
    Linknode *s = L->next;
    x = s->data;
    L->next = s->next;
    free(s);
    return true;
}

// 获取栈顶元素
bool GetTop(LiStack L, ElemType &x){
    if(L->next == NULL)
        return false;
    x = L->next->data;
    return true;
}

// 打印栈
void PrintStack(LiStack L){
    Linknode *p = L->next;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main(){
    LiStack L;
    InitStack(L);
    
    pushStack(L, 10);
    pushStack(L, 20);
    pushStack(L, 30);
    printf("栈元素：");
    PrintStack(L);
    
    int x;
    popStack(L, x);
    printf("出栈元素：%d\n", x);
    printf("栈元素：");
    PrintStack(L);
    
    GetTop(L, x);
    printf("栈顶元素：%d\n", x);
    
    return 0;
}