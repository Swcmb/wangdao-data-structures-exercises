#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
#define SUCCESS 1
#define UNSUCCESS 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;

// 顺序查找
int SequentialSearch(int a[], int n, int key){
    for(int i=0; i<n; i++){
        if(a[i] == key){
            return i;
        }
    }
    return -1;
}

// 顺序查找（哨兵）
int SequentialSearch_Sentinel(int a[], int n, int key){
    a[0] = key;
    int i = n;
    while(a[i] != key){
        i--;
    }
    return i;
}

// 折半查找
int BinarySearch(int a[], int n, int key){
    int low = 0, high = n-1;
    while(low <= high){
        int mid = (low + high) / 2;
        if(a[mid] == key){
            return mid;
        }else if(a[mid] > key){
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }
    return -1;
}

// 分块查找
// 索引表结构
typedef struct{
    int maxValue;
    int start;
}Index;

// 分块查找
int BlockSearch(Index index[], int m, int a[], int n, int key){
    int i = 0;
    while(i < m && key > index[i].maxValue){
        i++;
    }
    if(i >= m){
        return -1;
    }
    int j = index[i].start;
    while(j < n && a[j] != key){
        j++;
    }
    if(j < n){
        return j;
    }else{
        return -1;
    }
}

// 红黑树
#define RED 0
#define BLACK 1

typedef struct RBNode{
    ElemType key;
    int color;
    struct RBNode *left, *right, *parent;
}RBNode, *RBT;

// 左旋
void LeftRotate(RBT &T, RBNode *x){
    RBNode *y = x->right;
    x->right = y->left;
    if(y->left != NULL){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL){
        T = y;
    }else if(x == x->parent->left){
        x->parent->left = y;
    }else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// 右旋
void RightRotate(RBT &T, RBNode *y){
    RBNode *x = y->left;
    y->left = x->right;
    if(x->right != NULL){
        x->right->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == NULL){
        T = x;
    }else if(y == y->parent->left){
        y->parent->left = x;
    }else{
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

// 插入修复
void RBInsertFixup(RBT &T, RBNode *z){
    while(z->parent != NULL && z->parent->color == RED){
        if(z->parent == z->parent->parent->left){
            RBNode *y = z->parent->parent->right;
            if(y != NULL && y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else{
                if(z == z->parent->right){
                    z = z->parent;
                    LeftRotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RightRotate(T, z->parent->parent);
            }
        }else{
            RBNode *y = z->parent->parent->left;
            if(y != NULL && y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else{
                if(z == z->parent->left){
                    z = z->parent;
                    RightRotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftRotate(T, z->parent->parent);
            }
        }
    }
    T->color = BLACK;
}

// 插入
void RBInsert(RBT &T, ElemType key){
    RBNode *z = (RBNode *)malloc(sizeof(RBNode));
    z->key = key;
    z->color = RED;
    z->left = z->right = z->parent = NULL;
    
    RBNode *y = NULL;
    RBNode *x = T;
    while(x != NULL){
        y = x;
        if(z->key < x->key){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y == NULL){
        T = z;
    }else if(z->key < y->key){
        y->left = z;
    }else{
        y->right = z;
    }
    RBInsertFixup(T, z);
}

// 查找
RBNode* RBSearch(RBT T, ElemType key){
    RBNode *p = T;
    while(p != NULL && p->key != key){
        if(key < p->key){
            p = p->left;
        }else{
            p = p->right;
        }
    }
    return p;
}

// B树
#define MAX_KEYS 3 // 阶数为4
#define MIN_KEYS 1

typedef struct BTNode{
    int keynum;
    ElemType keys[MAX_KEYS];
    struct BTNode *parent;
    struct BTNode *child[MAX_KEYS+1];
}BTNode, *BTree;

// 查找
BTNode* BTreeSearch(BTree T, ElemType key){
    BTNode *p = T;
    while(p != NULL){
        int i = 0;
        while(i < p->keynum && key > p->keys[i]){
            i++;
        }
        if(i < p->keynum && key == p->keys[i]){
            return p;
        }
        p = p->child[i];
    }
    return NULL;
}

// 散列查找
#define HASHSIZE 10
#define NULLKEY -32768

typedef struct{
    ElemType *elem;
    int count;
}HashTable;

// 初始化散列表
int InitHashTable(HashTable &H){
    H.count = HASHSIZE;
    H.elem = (ElemType *)malloc(HASHSIZE * sizeof(ElemType));
    for(int i=0; i<HASHSIZE; i++){
        H.elem[i] = NULLKEY;
    }
    return SUCCESS;
}

// 散列函数
int Hash(ElemType key){
    return key % HASHSIZE;
}

// 插入
void InsertHash(HashTable &H, ElemType key){
    int addr = Hash(key);
    while(H.elem[addr] != NULLKEY){
        addr = (addr + 1) % HASHSIZE;
    }
    H.elem[addr] = key;
}

// 查找
int SearchHash(HashTable H, ElemType key, int &addr){
    addr = Hash(key);
    while(H.elem[addr] != NULLKEY){
        if(H.elem[addr] == key){
            return SUCCESS;
        }
        addr = (addr + 1) % HASHSIZE;
    }
    return UNSUCCESS;
}

// 打印散列表
void PrintHashTable(HashTable H){
    for(int i=0; i<HASHSIZE; i++){
        if(H.elem[i] != NULLKEY){
            printf("%d: %d\n", i, H.elem[i]);
        }else{
            printf("%d: NULL\n", i);
        }
    }
}

int main(){
    // 测试顺序查找
    printf("=== 顺序查找 ===\n");
    int a[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    int n = sizeof(a)/sizeof(a[0]);
    int key = 6;
    int pos = SequentialSearch(a, n, key);
    printf("顺序查找 %d 的位置: %d\n", key, pos);
    
    pos = SequentialSearch_Sentinel(a, n, key);
    printf("顺序查找（哨兵） %d 的位置: %d\n", key, pos);
    
    // 测试折半查找
    printf("\n=== 折半查找 ===\n");
    int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    pos = BinarySearch(b, n, key);
    printf("折半查找 %d 的位置: %d\n", key, pos);
    
    // 测试分块查找
    printf("\n=== 分块查找 ===\n");
    int c[] = {8, 14, 6, 9, 10, 22, 34, 18, 19, 31, 40, 38, 54, 66, 46, 71, 78, 68, 80, 85};
    int m = 4; // 4个块
    Index index[m];
    index[0].maxValue = 14;
    index[0].start = 0;
    index[1].maxValue = 34;
    index[1].start = 5;
    index[2].maxValue = 66;
    index[2].start = 10;
    index[3].maxValue = 85;
    index[3].start = 15;
    pos = BlockSearch(index, m, c, 20, 38);
    printf("分块查找 %d 的位置: %d\n", 38, pos);
    
    // 测试红黑树
    printf("\n=== 红黑树 ===\n");
    RBT T = NULL;
    int keys[] = {10, 20, 30, 15, 25, 5, 35};
    for(int i=0; i<7; i++){
        RBInsert(T, keys[i]);
    }
    RBNode *p = RBSearch(T, 25);
    if(p != NULL){
        printf("红黑树查找 25: 找到\n");
    }else{
        printf("红黑树查找 25: 未找到\n");
    }
    
    // 测试散列查找
    printf("\n=== 散列查找 ===\n");
    HashTable H;
    InitHashTable(H);
    int hash_keys[] = {12, 25, 36, 48, 59, 62, 73, 84};
    for(int i=0; i<8; i++){
        InsertHash(H, hash_keys[i]);
    }
    PrintHashTable(H);
    int addr;
    if(SearchHash(H, 36, addr) == SUCCESS){
        printf("散列查找 36: 找到，位置 %d\n", addr);
    }else{
        printf("散列查找 36: 未找到\n");
    }
    
    return 0;
}