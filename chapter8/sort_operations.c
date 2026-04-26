#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100

typedef int ElemType;

// 打印数组
void PrintArray(int a[], int n){
    for(int i=0; i<n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

// 直接插入排序
void InsertSort(int a[], int n){
    for(int i=1; i<n; i++){
        if(a[i] < a[i-1]){
            int temp = a[i];
            int j = i-1;
            while(j>=0 && a[j]>temp){
                a[j+1] = a[j];
                j--;
            }
            a[j+1] = temp;
        }
    }
}

// 折半插入排序
void BinaryInsertSort(int a[], int n){
    for(int i=1; i<n; i++){
        int temp = a[i];
        int low = 0, high = i-1;
        while(low <= high){
            int mid = (low + high)/2;
            if(a[mid] > temp){
                high = mid - 1;
            }else{
                low = mid + 1;
            }
        }
        for(int j=i-1; j>=high+1; j--){
            a[j+1] = a[j];
        }
        a[high+1] = temp;
    }
}

// 希尔排序
void ShellSort(int a[], int n){
    for(int d=n/2; d>=1; d=d/2){
        for(int i=d; i<n; i++){
            if(a[i] < a[i-d]){
                int temp = a[i];
                int j = i-d;
                while(j>=0 && a[j]>temp){
                    a[j+d] = a[j];
                    j = j-d;
                }
                a[j+d] = temp;
            }
        }
    }
}

// 冒泡排序
void BubbleSort(int a[], int n){
    for(int i=0; i<n-1; i++){
        bool flag = false;
        for(int j=0; j<n-i-1; j++){
            if(a[j] > a[j+1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                flag = true;
            }
        }
        if(!flag) break;
    }
}

// 快速排序
int Partition(int a[], int low, int high){
    int pivot = a[low];
    while(low < high){
        while(low < high && a[high] >= pivot) high--;
        a[low] = a[high];
        while(low < high && a[low] <= pivot) low++;
        a[high] = a[low];
    }
    a[low] = pivot;
    return low;
}

void QuickSort(int a[], int low, int high){
    if(low < high){
        int pivotpos = Partition(a, low, high);
        QuickSort(a, low, pivotpos-1);
        QuickSort(a, pivotpos+1, high);
    }
}

// 简单选择排序
void SelectSort(int a[], int n){
    for(int i=0; i<n-1; i++){
        int min = i;
        for(int j=i+1; j<n; j++){
            if(a[j] < a[min]){
                min = j;
            }
        }
        if(min != i){
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
}

// 堆排序
void HeapAdjust(int a[], int k, int len){
    a[0] = a[k];
    for(int i=2*k; i<=len; i*=2){
        if(i<len && a[i]<a[i+1]){
            i++;
        }
        if(a[0] >= a[i]){
            break;
        }else{
            a[k] = a[i];
            k = i;
        }
    }
    a[k] = a[0];
}

void BuildMaxHeap(int a[], int len){
    for(int i=len/2; i>0; i--){
        HeapAdjust(a, i, len);
    }
}

void HeapSort(int a[], int len){
    BuildMaxHeap(a, len);
    for(int i=len; i>1; i--){
        int temp = a[1];
        a[1] = a[i];
        a[i] = temp;
        HeapAdjust(a, 1, i-1);
    }
}

// 归并排序
void Merge(int a[], int low, int mid, int high){
    int b[MaxSize];
    for(int i=low; i<=high; i++){
        b[i] = a[i];
    }
    int i=low, j=mid+1, k=low;
    while(i<=mid && j<=high){
        if(b[i] <= b[j]){
            a[k++] = b[i++];
        }else{
            a[k++] = b[j++];
        }
    }
    while(i<=mid){
        a[k++] = b[i++];
    }
    while(j<=high){
        a[k++] = b[j++];
    }
}

void MergeSort(int a[], int low, int high){
    if(low < high){
        int mid = (low + high)/2;
        MergeSort(a, low, mid);
        MergeSort(a, mid+1, high);
        Merge(a, low, mid, high);
    }
}

// 基数排序
int GetMax(int a[], int n){
    int max = a[0];
    for(int i=1; i<n; i++){
        if(a[i] > max){
            max = a[i];
        }
    }
    return max;
}

int GetDigit(int x, int d){
    int div = 1;
    for(int i=1; i<d; i++){
        div *= 10;
    }
    return (x / div) % 10;
}

void RadixSort(int a[], int n){
    int max = GetMax(a, n);
    int digits = 0;
    while(max != 0){
        max /= 10;
        digits++;
    }
    
    int bucket[10][MaxSize];
    int count[10];
    
    for(int d=1; d<=digits; d++){
        for(int i=0; i<10; i++){
            count[i] = 0;
        }
        
        for(int i=0; i<n; i++){
            int digit = GetDigit(a[i], d);
            bucket[digit][count[digit]++] = a[i];
        }
        
        int k = 0;
        for(int i=0; i<10; i++){
            for(int j=0; j<count[i]; j++){
                a[k++] = bucket[i][j];
            }
        }
    }
}

int main(){
    int a[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = sizeof(a)/sizeof(a[0]);
    
    // 测试直接插入排序
    printf("=== 直接插入排序 ===\n");
    int b[MaxSize];
    memcpy(b, a, n*sizeof(int));
    InsertSort(b, n);
    PrintArray(b, n);
    
    // 测试折半插入排序
    printf("=== 折半插入排序 ===\n");
    memcpy(b, a, n*sizeof(int));
    BinaryInsertSort(b, n);
    PrintArray(b, n);
    
    // 测试希尔排序
    printf("=== 希尔排序 ===\n");
    memcpy(b, a, n*sizeof(int));
    ShellSort(b, n);
    PrintArray(b, n);
    
    // 测试冒泡排序
    printf("=== 冒泡排序 ===\n");
    memcpy(b, a, n*sizeof(int));
    BubbleSort(b, n);
    PrintArray(b, n);
    
    // 测试快速排序
    printf("=== 快速排序 ===\n");
    memcpy(b, a, n*sizeof(int));
    QuickSort(b, 0, n-1);
    PrintArray(b, n);
    
    // 测试简单选择排序
    printf("=== 简单选择排序 ===\n");
    memcpy(b, a, n*sizeof(int));
    SelectSort(b, n);
    PrintArray(b, n);
    
    // 测试堆排序
    printf("=== 堆排序 ===\n");
    int c[MaxSize];
    for(int i=0; i<n; i++){
        c[i+1] = a[i];
    }
    HeapSort(c, n);
    for(int i=1; i<=n; i++){
        printf("%d ", c[i]);
    }
    printf("\n");
    
    // 测试归并排序
    printf("=== 归并排序 ===\n");
    memcpy(b, a, n*sizeof(int));
    MergeSort(b, 0, n-1);
    PrintArray(b, n);
    
    // 测试基数排序
    printf("=== 基数排序 ===\n");
    memcpy(b, a, n*sizeof(int));
    RadixSort(b, n);
    PrintArray(b, n);
    
    return 0;
}