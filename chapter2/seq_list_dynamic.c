#include<stdio.h>
#include<stdlib.h>  //malloc、free函数的头文件 
#define InitSize 10 //默认的初始值

typedef struct{
	int  *data;    //指示动态分配数组的指针
	int MaxSize;   //顺序表的最大容量
	int length;    //顺序表的当前长度 
}SeqList; 

void InitList(SeqList &L){                 //初始化
	//用malloc 函数申请一片连续的存储空间
	L.data =(int*)malloc(InitSize*sizeof(int)) ;
	L.length=0;
	L.MaxSize=InitSize;
}

void IncreaseSize(SeqList &L,int len){  //增加动态数组的长度
	int *p=L.data;
	L.data=(int*)malloc((L.MaxSize+len)*sizeof(int));
	for(int i=0;i<L.length;i++){
		L.data[i]=p[i];      //将数据复制到新区域  
	}
	L.MaxSize=L.MaxSize+len; //顺序表最大长度增加len
	free(p);                 //释放原来的内存空间 
}

int main(){
	SeqList L;        //声明一个顺序表
	InitList(L);      //初始化顺序表
	IncreaseSize(L,5);//增加顺序表的长度
	return 0; 
}