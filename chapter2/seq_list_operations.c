#include<stdio.h>
#define MaxSize 10    //定义最大长度

typedef struct{
	int data[MaxSize];  //用静态的数组存放数据
	int length;         //顺序表的当前长度
}SqList;                //顺序表的类型定义 

void InitList(SqList &L){
	for(int i=0;i<MaxSize;i++){
		L.data[i]=0;
	}
	L.length=0;
}

// 插入操作
bool ListInsert(SqList &L, int i, int e){
	if(i<1||i>L.length+1)    //判断i的范围是否有效
		return false;
	if(L.length>=MaxSize) //当前存储空间已满，不能插入  
		return false;
	for(int j=L.length; j>=i; j--){    //将第i个元素及其之后的元素后移        
		L.data[j]=L.data[j-1];    
	}
	L.data[i-1]=e;  //在位置i处放入e
	L.length++;      //长度加1
	return true;
}

// 删除操作
bool ListDelete(SqList &L, int i, int &e) {
	if (i < 1 || i > L.length) // 判断i的范围是否有效
		return false;
	e = L.data[i-1]; // 将被删除的元素赋值给e 
	for (int j = i; j < L.length; j++) //将第i个位置后的元素前移 
		L.data[j-1] = L.data[j];
	L.length--;
	return true; 
}

// 按位查找
int GetElem(SqList L, int i) {
	return L.data[i-1];
}

// 按值查找
int LocateElem(SqList L, int e){
	for(int i=0; i<L.length; i++)
		if(L.data[i] == e)  
			return i+1;     //数组下标为i的元素值等于e，返回其位序i+1
	return 0;               //推出循环，说明查找失败
}

int main() {  
	SqList L;   //声明一个顺序表
	InitList(L);//初始化顺序表
	
	// 测试插入操作
	ListInsert(L, 1, 10);
	ListInsert(L, 2, 20);
	ListInsert(L, 3, 30);
	
	// 测试删除操作
	int e = -1;
	if (ListDelete(L, 2, e))
		printf("已删除第2个元素，删除元素值为%d\n", e);
	else
		printf("位序i不合法，删除失败\n"); 
	
	// 测试按位查找
	printf("第1个元素的值为%d\n", GetElem(L, 1));
	
	// 测试按值查找
	printf("值为30的元素位置为%d\n", LocateElem(L, 30));
	
	return 0;
}