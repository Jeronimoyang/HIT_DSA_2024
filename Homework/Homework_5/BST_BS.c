#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 3000
typedef struct celltype {
    int key;
    struct celltype *lchild, *rchild;
} BSTNode;
typedef BSTNode *BST;
// 生成测试数据
void Generation_of_Input1() {
    FILE *fp = fopen("Input1.txt", "w");
    if (fp == NULL) {
        printf("无法打开Input1.txt\n");
        exit(1);
    }
    for (int i = 0; i <= 2048; i++) {
        if (i % 2 == 1) {
            fprintf(fp, "%d\n", i);
        }
    }
    fclose(fp);
}
void Generation_of_Input2() {
    srand(time(NULL));
    int array[1024];
    int count = 0;
    for (int i = 1; i < 2048; i += 2) {  // 修正循环的起始值和终止条件
        array[count] = i;
        count++;
    }
    for (int i = 1023; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    FILE *fp = fopen("Input2.txt", "w");
    if (fp == NULL) {
        printf("无法打开Input2.txt\n");
        exit(1);
    }
    for (int i = 0; i < 1024; i++) {
        fprintf(fp, "%d\n", array[i]);
    }
    fclose(fp);
    printf("生成测试数据成功\n");
}
// BST的查找
BST BST_Search(BST T, int k, int *num) {
    BST p = T;
    while (p != NULL) {
        (*num)++;
        if (k == p->key) {
            return p;
        } else if (k > p->key) {
            p = p->rchild;
        } else {
            p = p->lchild;
        }
    }
    return p;
}
// BST的插入
int BST_Insert(BST *T, int k) {
    if (*T == NULL) {
        *T = (BST)malloc(sizeof(BSTNode));
        (*T)->key = k;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        return 1;
    } else if (k < (*T)->key)
        return BST_Insert(&(*T)->lchild, k);
    else if (k > (*T)->key)
        return BST_Insert(&(*T)->rchild, k);
    else
        return 0;
}
// BST的删除
int deletemin(BST *T) {
    int tmp;
    BST p;
    if ((*T)->lchild == NULL) {
        p = *T;
        tmp = (*T)->key;
        *T = (*T)->rchild;
        free(p);
        return tmp;
    } else
        return deletemin(&(*T)->lchild);
}
void BST_Delete(BST *T, int k) {
    if (*T != NULL) {
        if (k < (*T)->key)
            BST_Delete(&(*T)->lchild, k);
        else if (k > (*T)->key)
            BST_Delete(&(*T)->rchild, k);
        else {
            if ((*T)->rchild == NULL)
                *T = (*T)->lchild;
            else if ((*T)->lchild == NULL)
                *T = (*T)->rchild;
            else
                (*T)->key = deletemin(&(*T)->rchild);
        }
    }
}
// BST的排序（中序遍历）
void BST_InOrder(BST T) {
    if (T != NULL) {
        BST_InOrder(T->lchild);
        printf("%d ", T->key);
        BST_InOrder(T->rchild);
    }
}
// 创建BST(从数组中)
void CreateBST(BST *T, int a[], int n) {
    *T = NULL;
    for (int i = 0; i < n; i++) {
        BST_Insert(T, a[i]);
    }
}
// 计算BST的查找成功和失败的平均查找长度
void BST_Calculate_search_length(BST T) {
    int success = 0;
    int fail = 0;
    int num_success = 0;
    int num_fail = 0;
    double ASL_success = 0;
    double ASL_fail = 0;
    for (int i = 0; i <= 2048; i++) {
        if (i % 2 == 1) {
            success = success + 1;
            BST_Search(T, i, &num_success);
        } else if (i % 2 == 0) {
            fail = fail + 1;
            BST_Search(T, i, &num_fail);
        }
    }
    ASL_success = (double)num_success / success;
    ASL_fail = (double)num_fail / fail;
    printf("查找成功的平均查找长度为:%f\n", ASL_success);
    printf("查找失败的平均查找长度为:%f\n", ASL_fail);
}
// BST对Input1.txt操作
void BST_Input1() {
    BST T1;
    FILE *fp1 = fopen("Input1.txt", "r");
    if (fp1 == NULL) {
        printf("无法打开Input1.txt\n");
        exit(1);
    }
    int array_1[MAX];
    int n1 = 0;
    while (fscanf(fp1, "%d", &array_1[n1]) != EOF) {
        n1++;
    }
    fclose(fp1);
    CreateBST(&T1, array_1, n1);
    printf("BST在Input.txt1中查找:\n");
    BST_Calculate_search_length(T1);
}
// BST对Input2.txt操作
void BST_Input2() {
    BST T2;
    FILE *fp2 = fopen("Input2.txt", "r");
    if (fp2 == NULL) {
        printf("无法打开Input2.txt\n");
        exit(1);
    }
    int array_2[MAX];
    int n2 = 0;
    while (fscanf(fp2, "%d", &array_2[n2]) != EOF) {
        n2++;
    }
    fclose(fp2);
    CreateBST(&T2, array_2, n2);
    printf("BST在Input.txt2中查找:\n");
    BST_Calculate_search_length(T2);
}
// BST对Input_test.txt操作
void BST_Input_test() {
    BST T;
    FILE *fp = fopen("Input_test.txt", "r");
    if (fp == NULL) {
        printf("无法打开Input_test.txt\n");
        exit(1);
    }
    int array[MAX];
    int n = 0;
    while (fscanf(fp, "%d", &array[n]) != EOF) {
        n++;
    }
    fclose(fp);
    CreateBST(&T, array, n);
    int function_option;
    while (1) {
        printf(
            "请选择功能实现:\n1.插入+排序\n2.删除+排序\n3.查找\n0."
            "退出\n");
        scanf("%d", &function_option);
        if (function_option == 1) {
            int key;
            printf("请输入要插入的数:");
            scanf("%d", &key);
            if (BST_Insert(&T, key)) {
                printf("插入成功\n");
            } else {
                printf("插入失败\n");
            }
            printf("插入+排序结果为:");
            BST_InOrder(T);
            printf("\n");
        } else if (function_option == 2) {
            int key;
            printf("请输入要删除的数:");
            scanf("%d", &key);
            BST_Delete(&T, key);
            printf("删除成功\n");
            printf("删除+排序结果为:");
            BST_InOrder(T);
            printf("\n");
        } else if (function_option == 3) {
            int key;
            printf("请输入要查找的数:");
            scanf("%d", &key);
            BST p = BST_Search(T, key, &n);
            if (p != NULL) {
                printf("查找成功\n");
            } else {
                printf("查找失败\n");
            }
        } else if (function_option == 0) {
            break;
        } else {
            printf("输入错误，请重新输入\n");
        }
    }
}
// 非递归折半查找
int Binary_Search(int a[], int n, int key, int *count) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        (*count)++;
        mid = (low + high) / 2;
        if (a[mid] == key)
            return mid;
        else if (a[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}
// 递归折半查找
int Binary_Search_Recursive(int a[], int low, int high, int key, int *count) {
    if (low > high) {
        return -1;
    }
    (*count)++;
    int mid = (low + high) / 2;
    if (a[mid] == key) {
        return mid;
    } else if (a[mid] > key) {
        return Binary_Search_Recursive(a, low, mid - 1, key, count);
    } else {
        return Binary_Search_Recursive(a, mid + 1, high, key, count);
    }
}
// 计算非递归折半查找成功和失败的平均查找长度
void BS_Calculate_search_length() {
    FILE *fp3 = fopen("Input1.txt", "r");
    if (fp3 == NULL) {
        printf("无法打开Input1.txt\n");
        exit(1);
    }
    int array_3[MAX];
    int n3 = 0;
    while (fscanf(fp3, "%d", &array_3[n3]) != EOF) {
        n3++;
    }
    fclose(fp3);
    int count_success = 0;
    int count_fail = 0;
    int num_success = 0;
    int num_fail = 0;
    double ASL_success = 0;
    double ASL_fail = 0;
    for (int i = 0; i <= 2048; i++) {
        if (i % 2 == 1) {
            count_success++;
            Binary_Search(array_3, n3, i, &num_success);
        } else if (i % 2 == 0) {
            count_fail++;
            Binary_Search(array_3, n3, i, &num_fail);
        }
    }
    ASL_success = (double)num_success / count_success;
    ASL_fail = (double)num_fail / count_fail;
    printf("非递归折半查找:\n");
    printf("查找成功的平均查找长度为:%f\n", ASL_success);
    printf("查找失败的平均查找长度为:%f\n", ASL_fail);
}
// 计算递归折半查找成功和失败的平均查找长度
void BSR_Calculate_search_length() {
    FILE *fp4 = fopen("Input1.txt", "r");
    if (fp4 == NULL) {
        printf("无法打开Input1.txt\n");
        exit(1);
    }
    int array_4[MAX];
    int n4 = 0;
    while (fscanf(fp4, "%d", &array_4[n4]) != EOF) {
        n4++;
    }
    fclose(fp4);
    int count_success = 0;
    int count_fail = 0;
    int num_success = 0;
    int num_fail = 0;
    double ASL_success = 0;
    double ASL_fail = 0;
    for (int i = 0; i <= 2048; i++) {
        if (i % 2 == 1) {
            count_success++;
            Binary_Search_Recursive(array_4, 0, n4 - 1, i, &num_success);
        } else if (i % 2 == 0) {
            count_fail++;
            Binary_Search_Recursive(array_4, 0, n4 - 1, i, &num_fail);
        }
    }
    ASL_success = (double)num_success / count_success;
    ASL_fail = (double)num_fail / count_fail;
    printf("递归折半查找:\n");
    printf("查找成功的平均查找长度为:%f\n", ASL_success);
    printf("查找失败的平均查找长度为:%f\n", ASL_fail);
}
int main() {
    int function_option;
    while (1) {
        printf(
            "请选择功能实现:\n1.BST的基本操作(插入、删除、查找、排序)\n2."
            "生成测试数据\n3.实现BST查找;\n4."
            "实现非递归折半查找;\n5.实现递归折半查找;\n0.退出\n");
        scanf("%d", &function_option);
        if (function_option == 1) {
            BST_Input_test();
        } else if (function_option == 2) {
            Generation_of_Input1();
            Generation_of_Input2();
        } else if (function_option == 3) {
            BST_Input1();
            BST_Input2();
        } else if (function_option == 4) {
            BS_Calculate_search_length();
        } else if (function_option == 5) {
            BSR_Calculate_search_length();
        } else if (function_option == 0) {
            break;
        } else {
            printf("输入错误，请重新输入\n");
        }
    }
    return 0;
}