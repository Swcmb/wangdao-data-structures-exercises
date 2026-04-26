#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100

typedef int ElemType;

// 二叉树的链式存储
typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

// 初始化二叉树
void InitBiTree(BiTree &T){
    T = NULL;
}

// 创建二叉树
BiTree CreateBiTree(){
    ElemType ch;
    scanf("%d", &ch);
    if(ch == -1){
        return NULL;
    }
    BiTree T = (BiTree)malloc(sizeof(BiTNode));
    T->data = ch;
    T->lchild = CreateBiTree();
    T->rchild = CreateBiTree();
    return T;
}

// 先序遍历
void PreOrder(BiTree T){
    if(T != NULL){
        printf("%d ", T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

// 中序遍历
void InOrder(BiTree T){
    if(T != NULL){
        InOrder(T->lchild);
        printf("%d ", T->data);
        InOrder(T->rchild);
    }
}

// 后序遍历
void PostOrder(BiTree T){
    if(T != NULL){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%d ", T->data);
    }
}

// 层序遍历
void LevelOrder(BiTree T){
    BiTree queue[MaxSize];
    int front = 0, rear = 0;
    if(T != NULL){
        queue[rear++] = T;
    }
    while(front < rear){
        BiTree p = queue[front++];
        printf("%d ", p->data);
        if(p->lchild != NULL){
            queue[rear++] = p->lchild;
        }
        if(p->rchild != NULL){
            queue[rear++] = p->rchild;
        }
    }
}

// 线索二叉树
typedef struct ThreadNode{
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;
}ThreadNode, *ThreadTree;

// 全局变量，指向当前访问节点的前驱
ThreadNode *pre = NULL;

// 中序线索化
void InThread(ThreadTree T){
    if(T != NULL){
        InThread(T->lchild);
        if(T->lchild == NULL){
            T->lchild = pre;
            T->ltag = 1;
        }else{
            T->ltag = 0;
        }
        if(pre != NULL && pre->rchild == NULL){
            pre->rchild = T;
            pre->rtag = 1;
        }else if(pre != NULL){
            pre->rtag = 0;
        }
        pre = T;
        InThread(T->rchild);
    }
}

// 创建中序线索树
void CreateInThread(ThreadTree T){
    pre = NULL;
    if(T != NULL){
        InThread(T);
        if(pre->rchild == NULL){
            pre->rtag = 1;
        }
    }
}

// 二叉排序树
// 查找
BiTree SearchBST(BiTree T, ElemType key){
    if(T == NULL || T->data == key){
        return T;
    }else if(key < T->data){
        return SearchBST(T->lchild, key);
    }else{
        return SearchBST(T->rchild, key);
    }
}

// 插入
bool InsertBST(BiTree &T, ElemType key){
    if(T == NULL){
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = key;
        T->lchild = T->rchild = NULL;
        return true;
    }else if(key == T->data){
        return false;
    }else if(key < T->data){
        return InsertBST(T->lchild, key);
    }else{
        return InsertBST(T->rchild, key);
    }
}

// 删除
BiTree DeleteBST(BiTree &T, ElemType key){
    if(T == NULL){
        return NULL;
    }else if(key < T->data){
        T->lchild = DeleteBST(T->lchild, key);
    }else if(key > T->data){
        T->rchild = DeleteBST(T->rchild, key);
    }else{
        if(T->lchild == NULL){
            BiTree temp = T;
            T = T->rchild;
            free(temp);
        }else if(T->rchild == NULL){
            BiTree temp = T;
            T = T->lchild;
            free(temp);
        }else{
            BiTree temp = T->rchild;
            while(temp->lchild != NULL){
                temp = temp->lchild;
            }
            T->data = temp->data;
            T->rchild = DeleteBST(T->rchild, temp->data);
        }
    }
    return T;
}

// 平衡二叉树
// 计算树的高度
int GetHeight(BiTree T){
    if(T == NULL){
        return 0;
    }
    int lh = GetHeight(T->lchild);
    int rh = GetHeight(T->rchild);
    return lh > rh ? lh + 1 : rh + 1;
}

// 平衡因子
int GetBalanceFactor(BiTree T){
    if(T == NULL){
        return 0;
    }
    return GetHeight(T->lchild) - GetHeight(T->rchild);
}

// 右旋
BiTree R_Rotate(BiTree T){
    BiTree L = T->lchild;
    T->lchild = L->rchild;
    L->rchild = T;
    return L;
}

// 左旋
BiTree L_Rotate(BiTree T){
    BiTree R = T->rchild;
    T->rchild = R->lchild;
    R->lchild = T;
    return R;
}

// 左平衡旋转
BiTree LeftBalance(BiTree T){
    BiTree L = T->lchild;
    switch(GetBalanceFactor(L)){
        case 1: // LL型
            return R_Rotate(T);
        case -1: // LR型
            T->lchild = L_Rotate(L);
            return R_Rotate(T);
    }
    return T;
}

// 右平衡旋转
BiTree RightBalance(BiTree T){
    BiTree R = T->rchild;
    switch(GetBalanceFactor(R)){
        case -1: // RR型
            return L_Rotate(T);
        case 1: // RL型
            T->rchild = R_Rotate(R);
            return L_Rotate(T);
    }
    return T;
}

// 平衡二叉树插入
BiTree InsertAVL(BiTree &T, ElemType key){
    if(T == NULL){
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = key;
        T->lchild = T->rchild = NULL;
    }else if(key < T->data){
        T->lchild = InsertAVL(T->lchild, key);
        if(GetBalanceFactor(T) == 2){
            T = LeftBalance(T);
        }
    }else if(key > T->data){
        T->rchild = InsertAVL(T->rchild, key);
        if(GetBalanceFactor(T) == -2){
            T = RightBalance(T);
        }
    }
    return T;
}

// 哈夫曼树
// 哈夫曼节点
typedef struct HTNode{
    ElemType weight;
    int parent, lchild, rchild;
}HTNode, *HuffmanTree;

// 选择两个最小的节点
void Select(HuffmanTree HT, int n, int &s1, int &s2){
    int min1 = 9999, min2 = 9999;
    for(int i=1; i<=n; i++){
        if(HT[i].parent == 0){
            if(HT[i].weight < min1){
                min2 = min1;
                s2 = s1;
                min1 = HT[i].weight;
                s1 = i;
            }else if(HT[i].weight < min2){
                min2 = HT[i].weight;
                s2 = i;
            }
        }
    }
}

// 创建哈夫曼树
void CreateHuffmanTree(HuffmanTree &HT, int n, ElemType *w){
    if(n <= 1) return;
    int m = 2 * n - 1;
    HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
    for(int i=1; i<=n; i++){
        HT[i].weight = w[i-1];
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for(int i=n+1; i<=m; i++){
        HT[i].weight = 0;
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for(int i=n+1; i<=m; i++){
        int s1, s2;
        Select(HT, i-1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

// 打印哈夫曼树
void PrintHuffmanTree(HuffmanTree HT, int m){
    printf("节点	权值	父节点	左孩子	右孩子\n");
    for(int i=1; i<=m; i++){
        printf("%d	%d	%d	%d	%d\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
    }
}

int main(){
    // 测试二叉树
    printf("=== 二叉树 ===\n");
    BiTree T;
    InitBiTree(T);
    printf("请输入二叉树节点值（-1表示空）：");
    T = CreateBiTree();
    
    printf("先序遍历：");
    PreOrder(T);
    printf("\n");
    
    printf("中序遍历：");
    InOrder(T);
    printf("\n");
    
    printf("后序遍历：");
    PostOrder(T);
    printf("\n");
    
    printf("层序遍历：");
    LevelOrder(T);
    printf("\n");
    
    // 测试二叉排序树
    printf("\n=== 二叉排序树 ===\n");
    BiTree BST = NULL;
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    for(int i=0; i<7; i++){
        InsertBST(BST, keys[i]);
    }
    printf("中序遍历BST：");
    InOrder(BST);
    printf("\n");
    
    // 测试平衡二叉树
    printf("\n=== 平衡二叉树 ===\n");
    BiTree AVL = NULL;
    for(int i=0; i<7; i++){
        AVL = InsertAVL(AVL, keys[i]);
    }
    printf("中序遍历AVL：");
    InOrder(AVL);
    printf("\n");
    
    // 测试哈夫曼树
    printf("\n=== 哈夫曼树 ===\n");
    HuffmanTree HT;
    ElemType w[] = {5, 29, 7, 8, 14, 23, 3, 11};
    int n = 8;
    CreateHuffmanTree(HT, n, w);
    PrintHuffmanTree(HT, 2*n-1);
    
    return 0;
}