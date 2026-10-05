#include "a.h"

// 初始化顺序表
void InitList(SqList &L) {
    L.length = 0;
}

// 在位置 i 插入元素 e
bool ListInsert(SqList &L, int i, int e) {
    if (i < 1 || i > L.length + 1)
        return false;
    if (L.length >= MaxSize)
        return false;
    for (int j = L.length; j >= i; j--)
        L.data[j] = L.data[j-1];
    L.data[i-1] = e;
    L.length++;
    return true;
}

// 删除位置 i 的元素，并将其值存储在 e 中
bool ListDelete(SqList &L, int i, int &e) {
    if (i < 1 || i > L.length)
        return false;
    e = L.data[i-1];
    for (int j = i; j < L.length; j++) {
        L.data[j-1] = L.data[j];
    }
    L.length--;
    return true;
}

// 查找元素 e 在顺序表中的位置
int LocateElem(SqList L, int e) {
    int i;
    for (i = 0; i < L.length; i++) {
        if (L.data[i] == e)
            return i + 1;
    }
    return 0;
}