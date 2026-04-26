#include<stdio.h>
#include<string.h>
#define MaxSize 100

// 串的静态数组实现
typedef struct{
    char ch[MaxSize];
    int length;
}SString;

// 初始化串
void InitString(SString &S){
    S.length = 0;
    memset(S.ch, 0, sizeof(S.ch));
}

// 赋值操作
void StrAssign(SString &S, char *chars){
    int len = strlen(chars);
    for(int i=0; i<len; i++){
        S.ch[i] = chars[i];
    }
    S.length = len;
}

// 复制操作
void StrCopy(SString &T, SString S){
    for(int i=0; i<S.length; i++){
        T.ch[i] = S.ch[i];
    }
    T.length = S.length;
}

// 判空操作
bool StrEmpty(SString S){
    return S.length == 0;
}

// 比较操作
int StrCompare(SString S, SString T){
    for(int i=0; i<S.length && i<T.length; i++){
        if(S.ch[i] != T.ch[i]){
            return S.ch[i] - T.ch[i];
        }
    }
    return S.length - T.length;
}

// 求串长
int StrLength(SString S){
    return S.length;
}

// 串联接
bool Concat(SString &T, SString S1, SString S2){
    if(S1.length + S2.length > MaxSize){
        return false;
    }
    for(int i=0; i<S1.length; i++){
        T.ch[i] = S1.ch[i];
    }
    for(int i=0; i<S2.length; i++){
        T.ch[S1.length + i] = S2.ch[i];
    }
    T.length = S1.length + S2.length;
    return true;
}

// 求子串
bool SubString(SString &Sub, SString S, int pos, int len){
    if(pos < 1 || pos > S.length || len < 0 || pos + len - 1 > S.length){
        return false;
    }
    for(int i=0; i<len; i++){
        Sub.ch[i] = S.ch[pos-1 + i];
    }
    Sub.length = len;
    return true;
}

// 朴素模式匹配算法
int Index(SString S, SString T){
    int i = 1, j = 1;
    while(i <= S.length && j <= T.length){
        if(S.ch[i-1] == T.ch[j-1]){
            i++;
            j++;
        }else{
            i = i - j + 2;
            j = 1;
        }
    }
    if(j > T.length){
        return i - T.length;
    }else{
        return 0;
    }
}

// KPM算法
// 计算next数组
void getNext(SString T, int next[]){
    int i = 1, j = 0;
    next[1] = 0;
    while(i < T.length){
        if(j == 0 || T.ch[i-1] == T.ch[j-1]){
            i++;
            j++;
            next[i] = j;
        }else{
            j = next[j];
        }
    }
}

// KPM模式匹配
int Index_KMP(SString S, SString T, int next[]){
    int i = 1, j = 1;
    while(i <= S.length && j <= T.length){
        if(j == 0 || S.ch[i-1] == T.ch[j-1]){
            i++;
            j++;
        }else{
            j = next[j];
        }
    }
    if(j > T.length){
        return i - T.length;
    }else{
        return 0;
    }
}

// 优化的next数组
void getNextVal(SString T, int nextval[]){
    int i = 1, j = 0;
    nextval[1] = 0;
    while(i < T.length){
        if(j == 0 || T.ch[i-1] == T.ch[j-1]){
            i++;
            j++;
            if(T.ch[i-1] != T.ch[j-1]){
                nextval[i] = j;
            }else{
                nextval[i] = nextval[j];
            }
        }else{
            j = nextval[j];
        }
    }
}

// 打印串
void PrintString(SString S){
    for(int i=0; i<S.length; i++){
        printf("%c", S.ch[i]);
    }
    printf("\n");
}

int main(){
    SString S, T, Sub, ConcatStr;
    InitString(S);
    InitString(T);
    InitString(Sub);
    InitString(ConcatStr);
    
    // 测试串操作
    StrAssign(S, "Hello, World!");
    StrAssign(T, "World");
    
    printf("S: ");
    PrintString(S);
    printf("T: ");
    PrintString(T);
    
    printf("S长度: %d\n", StrLength(S));
    printf("T长度: %d\n", StrLength(T));
    
    // 测试比较
    int cmp = StrCompare(S, T);
    printf("S与T比较结果: %d\n", cmp);
    
    // 测试子串
    SubString(Sub, S, 8, 5);
    printf("S的子串(8,5): ");
    PrintString(Sub);
    
    // 测试串联接
    Concat(ConcatStr, S, T);
    printf("S与T连接: ");
    PrintString(ConcatStr);
    
    // 测试朴素模式匹配
    int pos = Index(S, T);
    printf("朴素模式匹配结果: %d\n", pos);
    
    // 测试KPM算法
    int next[MaxSize];
    getNext(T, next);
    printf("next数组: ");
    for(int i=1; i<=T.length; i++){
        printf("%d ", next[i]);
    }
    printf("\n");
    
    int pos_kmp = Index_KMP(S, T, next);
    printf("KPM模式匹配结果: %d\n", pos_kmp);
    
    // 测试优化的nextval数组
    int nextval[MaxSize];
    getNextVal(T, nextval);
    printf("nextval数组: ");
    for(int i=1; i<=T.length; i++){
        printf("%d ", nextval[i]);
    }
    printf("\n");
    
    return 0;
}