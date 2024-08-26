#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100000
// 生成数据，第一行为一个整数n(表示带排列序列的长度)，第二行有n个整数，表示待排序的序列
void Data_generation(int data_size) {
    srand((unsigned)time(NULL));
    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL) {
        printf("File open failed!\n");
        exit(0);
    }
    fprintf(fp, "%d\n", data_size);
    for (int i = 0; i < data_size; i++) {
        fprintf(fp, "%d ", rand() % 100000);
    }
    fclose(fp);
}
// 读取数据
void Data_retrieve(int array[], int *high) {
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("File open failed!\n");
        exit(0);
    }
    fscanf(fp, "%d", high);
    for (int i = 0; i < *high; i++) {
        fscanf(fp, "%d", &array[i]);
    }
    fclose(fp);
}
// 复制数据
void Data_Copy(int array[], int a[], int b[], int c[], int high) {
    for (int i = 0; i < high; i++) {
        a[i] = array[i];
        b[i] = array[i];
        c[i] = array[i];
    }
}
// 归并排序(分支算法)
void Merge_Sort_Recursive(int arr[], int reg[], int start, int end) {
    if (start >= end) {
        return;
    }
    int len = end - start, mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    Merge_Sort_Recursive(arr, reg, start1, end1);
    Merge_Sort_Recursive(arr, reg, start2, end2);
    int k = start;
    while (start1 <= end1 && start2 <= end2) {
        reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    }
    while (start1 <= end1) {
        reg[k++] = arr[start1++];
    }
    while (start2 <= end2) {
        reg[k++] = arr[start2++];
    }
    for (k = start; k <= end; k++) {
        arr[k] = reg[k];
    }
}
void Merge_Sort(int arr[], const int len) {
    int reg[len];  // 用于存放归并后的数据
    Merge_Sort_Recursive(arr, reg, 0, len - 1);  // 递归调用
}
// 快速排序(分治算法)
void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}
void Quick_Sort_Recursive(int arr[], int start, int end) {
    if (start >= end) {
        return;
    }
    int mid = arr[end];
    int left = start, right = end - 1;
    while (left < right) {
        while (arr[left] < mid && left < right) {
            left++;
        }
        while (arr[right] >= mid && left < right) {
            right--;
        }
        swap(&arr[left], &arr[right]);
    }
    if (arr[left] >= arr[end]) {
        swap(&arr[left], &arr[end]);
    } else {
        left++;
    }
    if (left) {
        Quick_Sort_Recursive(arr, start, left - 1);
    }
    Quick_Sort_Recursive(arr, left + 1, end);
}
void Quick_Sort(int arr[], int len) { Quick_Sort_Recursive(arr, 0, len - 1); }
// 插入排序
void Insert_Sort(int arr[], int high) {
    for (int i = 1; i < high; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}
// 将排序后的数据写入文件(从函数的sortname参数中获取排序方法的名称，并将排序后的数据写入文件sortname.txt中)
void Data_Write(int arr[], int high, int sort_number) {
    FILE *fp;
    if (sort_number == 1) {
        fp = fopen("Merge_Sort.txt", "w");
    } else if (sort_number == 2) {
        fp = fopen("Quick_Sort.txt", "w");
    } else if (sort_number == 3) {
        fp = fopen("Insert_Sort.txt", "w");
    }
    if (fp == NULL) {
        printf("File open failed!\n");
        exit(0);
    }
    fprintf(fp, "%d\n", high);
    for (int i = 0; i < high; i++) {
        fprintf(fp, "%d ", arr[i]);
    }
    fclose(fp);
}
// 检测是否为升序
void Detecting_ascending_order(int arr[], int high) {
    for (int i = 0; i < high - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            printf("The data is not in ascending order!\n");
            return;
        }
    }
    printf("The data is in ascending order!\n");
}
int main() {
    int array[MAX], a[MAX], b[MAX], c[MAX];
    int high;
    int data_size;
    double sum_time;
    clock_t start_t, end_t;
    for (int data_size = 10000; data_size <= 100000;
         data_size = data_size + 10000) {
        printf("Data size: %d\n", data_size);
        Data_generation(data_size);
        Data_retrieve(array, &high);
        Data_Copy(array, a, b, c, high);

        start_t = clock();
        Merge_Sort(a, high);
        end_t = clock();
        Detecting_ascending_order(a, high);
        sum_time = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
        printf("Time of Merge Sort: %f(ms)\n", sum_time * 1000);
        Data_Write(a, high, 1);

        start_t = clock();
        Quick_Sort(b, high);
        end_t = clock();
        Detecting_ascending_order(b, high);
        sum_time = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
        printf("Time of Quick Sort: %f(ms)\n", sum_time * 1000);
        Data_Write(b, high, 2);

        start_t = clock();
        Insert_Sort(c, high);
        end_t = clock();
        Detecting_ascending_order(c, high);
        sum_time = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
        printf("Time of Insert Sort: %f(ms)\n", sum_time * 1000);
        Data_Write(c, high, 3);
    }
    return 0;
}