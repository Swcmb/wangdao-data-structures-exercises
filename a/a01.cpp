// 01.从顺序表中删除具有最小值的元素(假设唯一)并由函数返回被删元素的值。
// 空出的位置由最后一个元素填补，若顺序表为空，则显示出错信息并退出运行。
#include "a.h"

int main() {
    SqList L;
    InitList(L);

    // 测试插入操作
    ListInsert(L, 1, 10);
    ListInsert(L, 2, 20);
    ListInsert(L, 3, 30);

    // 测试查找操作
    int pos = LocateElem(L, 20);
    printf("元素 20 的位置: %d\n", pos);

    // 测试删除操作
    int e;
    bool success = ListDelete(L, 2, e);
    if (success) {
        printf("删除的元素: %d\n", e);
    }

    // 打印修改后的顺序表
    printf("修改后的顺序表: ");
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");

    return 0;
}