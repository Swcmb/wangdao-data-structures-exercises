#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

// 初始化空的单链表（不带头节点）
bool InitList(LinkList &L){
    L = NULL; //空表，暂时还没有任何结点
    return true;
}

// 初始化单链表（带头结点）
bool InitListWithHead(LinkList &L){
    L = (LNode*) malloc(sizeof(LNode));  //头指针指向的结点——分配一个头结点（不存储数据）
    if (L == NULL)          //内存不足，分配失败
        return false;
    L->next = NULL;       //头结点之后暂时还没有结点
    return true;
}

// 判断单链表是否为空（不带头节点）
bool Empty(LinkList L){
    return (L==NULL);
}

// 判断单链表是否为空（带头结点）
bool EmptyWithHead(LinkList L){
    if (L->next == NULL)
        return true;
    else
        return false;
}

// 按位序插入（带头结点）
bool ListInsert(LinkList &L, int i, ElemType e){
    if(i<1)
        return false;
    LNode *p;       //指针p指向当前扫描到的结点     
    int j=0;        //当前p指向的是第几个结点
    p = L;          //L指向头结点，头结点是第0个结点（不存数据）
    while(p!=NULL && j<i-1){     //如果i>lengh, p最后会等于NULL
        p = p->next;             //p指向下一个结点
        j++;
    }
    if (p==NULL)                 //如果p指针知道最后再往后就是NULL
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode)); //申请一个结点
    s->data = e;
    s->next = p->next;
    p->next = s;                 //将结点s连到p后,后两步千万不能颠倒
    return true;
}

// 后插操作
bool InsertNextNode(LNode *p, ElemType e){
    if(p==NULL){
        return false;
    }
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if(s==NULL)
        return false;
    s->data = e;          //用结点s保存数据元素e     
    s->next = p->next;
    p->next = s;          //将结点s连到p之后
    return true;
}

// 前插操作
bool InsertPriorNode(LNode *p, ElemType e){
    if(p==NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if(s==NULL) //内存分配失败
        return false;
    s->next = p->next;
    p->next = s;       //新结点s连到p之后
    s->data = p->data; //将p中元素复制到s
    p->data = e;       //p中元素覆盖为e
    return true;
}

// 按位序删除节点
bool ListDelete(LinkList &L, int i, ElemType &e){
    if(i<1) return false;
    LNode *p;       //指针p指向当前扫描到的结点     
    int j=0;        //当前p指向的是第几个结点
    p = L;          //L指向头结点，头结点是第0个结点（不存数据）
    while(p!=NULL && j<i-1){     //如果i>lengh, p最后会等于NULL
        p = p->next;             //p指向下一个结点
        j++;
    }
    if(p==NULL) return false;
    if(p->next == NULL) //第i-1个结点之后已无其他结点
        return false;
    LNode *q = p->next;         //令q指向被删除的结点
    e = q->data;                //用e返回被删除元素的值
    p->next = q->next;          //将*q结点从链中“断开”
    free(q);                     //释放结点的存储空间
    return true;
}

// 指定结点的删除
bool DeleteNode(LNode *p){
    if(p==NULL)
        return false;
    LNode *q = p->next;      //令q指向*p的后继结点
    p->data = p->next->data; //让p和后继结点交换数据域
    p->next = q->next;       //将*q结点从链中“断开”
    free(q);
    return true;
}

// 按位查找
LNode* GetElem(LinkList L, int i){
    if(i<0) return NULL;
    LNode *p;               //指针p指向当前扫描到的结点
    int j=0;                //当前p指向的是第几个结点
    p = L;                  //L指向头结点,头结点是第0个结点(不存数据)
    while(p!=NULL && j<i){  //循环找到第i个结点
        p = p->next;
        j++;
    }
    return p;               //返回p指针指向的值
}

// 按值查找
LNode* LocateElem(LinkList L, ElemType e){
    LNode *p = L->next;    //p指向第一个结点
    while(p!=NULL && p->data != e){
        p = p->next;
    }
    return p;           //找到后返回该结点指针，否则返回NULL
}

// 求单链表的长度
int Length(LinkList L){
    int len=0;       //统计表长
    LNode *p = L;
    while(p->next != NULL){
        p = p->next;
        len++;
    }
    return len;
}

// 尾插法建立单链表
LinkList List_TailInsert(LinkList &L){
    int x;            //设ElemType为整型int      
    L = (LinkList)malloc(sizeof(LNode));     //建立头结点(初始化空表)
    LNode *s, *r = L;                        //r为表尾指针
    printf("请输入数据，输入9999结束：");
    scanf("%d", &x);                         //输入要插入的结点的值
    while(x!=9999){                          //输入9999表示结束
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;                               //r指针指向新的表尾结点
        scanf("%d", &x);
    }
    r->next = NULL;                          //尾结点指针置空
    return L;
}

// 头插法建立单链表
LinkList List_HeadInsert(LinkList &L){
    LNode *s;
    int x;
    L = (LinkList)malloc(sizeof(LNode));     //建立头结点
    L->next = NULL;                          //初始为空链表,这步不能少！
    printf("请输入数据，输入9999结束：");
    scanf("%d", &x);                         //输入要插入的结点的值
    while(x!=9999){                          //输入9999表结束
        s = (LNode *)malloc(sizeof(LNode));  //创建新结点
        s->data = x;
        s->next = L->next;
        L->next = s;                         //将新结点插入表中，L为头指针
        scanf("%d", &x);
    }
    return L;
}

// 链表的逆置
LinkList ReverseList(LinkList L){
    LNode *p, *q;
    p = L->next;     //p指针指向第一个结点
    L->next = NULL;  //头结点指向NULL
    while (p != NULL){
        q = p;
        p = p->next;
        q->next = L->next;
        L->next = q;
    }
    return L;
}

// 打印链表
void PrintList(LinkList L){
    LNode *p = L->next;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main(){
    LinkList L;
    InitListWithHead(L);
    
    // 测试插入操作
    ListInsert(L, 1, 10);
    ListInsert(L, 2, 20);
    ListInsert(L, 3, 30);
    printf("插入后链表：");
    PrintList(L);
    
    // 测试删除操作
    int e;
    ListDelete(L, 2, e);
    printf("删除后链表：");
    PrintList(L);
    
    // 测试查找操作
    LNode *p = GetElem(L, 1);
    printf("第1个元素：%d\n", p->data);
    
    p = LocateElem(L, 30);
    printf("值为30的元素：%d\n", p->data);
    
    // 测试链表长度
    printf("链表长度：%d\n", Length(L));
    
    // 测试链表逆置
    ReverseList(L);
    printf("逆置后链表：");
    PrintList(L);
    
    return 0;
}