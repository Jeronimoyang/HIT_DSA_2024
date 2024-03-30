#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 无递归的冒泡排序
void bubbleSort(int array[], int len) {
    int temp, i, j;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
// 有递归的冒泡排序
void recursion_bubbleSort(int array[], int len) {
    int temp, i;
    for (i = 0; i < len - 1; i++) {
        if (array[i] > array[i + 1]) {
            temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;
        }
    }
    len--;
    if (len != 0) {
        return recursion_bubbleSort(array, len);
    }
}
// 无递归的选择排序
void selectionSort(int array[], int len) {
    int k, temp, i, j;
    for (i = 0; i < len - 1; i++) {
        k = i;
        for (j = i + 1; j < len; j++) {
            if (array[j] < array[k]) {
                k = j;
            }
        }
        if (k != i) {
            temp = array[k];
            array[k] = array[i];
            array[i] = temp;
        }
    }
}
// 有递归的选择排序
void recursion_selectionSort(int array[], int len) {
    int k, i, j, temp;
    j = len - 1;
    k = len - 1;
    for (i = len - 2; i >= 0; i--) {
        if (array[i] > array[k]) {
            k = i;
        }
    }
    if (j != k) {
        temp = array[k];
        array[k] = array[j];
        array[j] = temp;
    }
    len--;
    if (len != 1) {
        return recursion_selectionSort(array, len);
    }
}
// 无递归的插入排序
void insertSort(int array[], int len) {
    int key, i, j;
    for (i = 1; i < len; i++) {
        key = array[i];
        for (j = i - 1; j >= 0; j--) {
            if (array[j] > key) {
                array[j + 1] = array[j];
            } else {
                break;
            }
            array[j] = key;
        }
    }
}
// 有递归的插入排序
void recursion_insertSort(int array[], int len, int num) {
    int key;
    key = array[num];
    for (int i = num - 1; i >= 0; i--) {
        if (array[i] > key) {
            array[i + 1] = array[i];
        } else {
            break;
        }
        array[i] = key;
    }
    num++;
    if (num != len) {
        return recursion_insertSort(array, len, num);
    }
}

int main() {
    int sort_Way, len;
    srand((unsigned)time(NULL));
    len = 30000;
    int array[len];
    clock_t start, end;
    for (int i = 0; i < len; i++) {
        array[i] = rand() % 50000;
    }
    /*
    for (int i = 0; i < len; i++) {
        printf("%d\n", array[i]);
    }
    */
    printf(
        "选择排序方法：1.无递归的冒泡排序；2.无递归的选择排序；3."
        "无递归的插入排序；4.有递归的冒泡排序；5.有递归的选择排序；6."
        "有递归的插入排序");

    scanf("%d", &sort_Way);
    if (sort_Way == 1) {
        start = clock();
        bubbleSort(array, len);
        end = clock();
        printf("The time of bubbleSort is %lfs",
               (double)(end - start) / CLK_TCK);
        /*
        for (int i = 0; i < len; i++) {
            printf("%d\n", array[i]);
        }
        */
    } else if (sort_Way == 2) {
        start = clock();
        selectionSort(array, len);
        end = clock();
        printf("The time of selectionSort is %lfs",
               (double)(end - start) / CLK_TCK);
        /*
        for (int i = 0; i < len; i++) {
            printf("%d\n", array[i]);
        }
        */
    } else if (sort_Way == 3) {
        start = clock();
        insertSort(array, len);
        end = clock();
        printf("The time of insertSort is %lfs",
               (double)(end - start) / CLK_TCK);
        /*
        for (int i = 0; i < len; i++) {
            printf("%d\n", array[i]);
        }
        */
    } else if (sort_Way == 4) {
        start = clock();
        recursion_bubbleSort(array, len);
        end = clock();
        printf("The time of recursion_bubbleSort is %lfs",
               (double)(end - start) / CLK_TCK);

        /*
        for (int i = 0; i < len; i++) {
            printf("%d\n", array[i]);
        }
        */
    } else if (sort_Way == 5) {
        start = clock();
        recursion_selectionSort(array, len);
        end = clock();
        printf("The time of recursion_selectionSort is %lfs",
               (double)(end - start) / CLK_TCK);
        /*
        for (int i = 0; i < len; i++) {
            printf("%d\n", array[i]);
        }
        */
    } else if (sort_Way == 6) {
        start = clock();
        recursion_insertSort(array, len, 1);
        end = clock();
        printf("The time of recursion_insertSort is %lfs",
               (double)(end - start) / CLK_TCK);
        /*
        for (int i = 0; i < len; i++) {
            printf("%d\n", array[i]);
        }
        */
    }
    return 0;
}
