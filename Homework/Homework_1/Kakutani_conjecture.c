#include <stdio.h>
#include <stdlib.h>

// 判断所有100以内的正整数经过角谷猜想处理最后是否为1
int jiaogu(int num) {
    if (num == 1) {
        return num;
    } else if (num % 2 == 0) {
        num = num / 2;
    } else {
        num = num * 3 + 1;
    }
    return jiaogu(num);
}

// 对100以内的正整数进行测试验证，并找出其中最长的序列
int bingbao(int num) {
    int key = 0;
    while (1) {
        if (num == 1) {
            break;
        } else if (num % 2 == 0) {
            key++;
            num = num / 2;
        } else {
            key++;
            num = num * 3 + 1;
        }
    }
    return key;
}

int main() {
    printf(
        "请输入问题序号：1."
        "判断所有100以内的正整数经过角谷猜想处理最后是否为1；2.对100 "
        "以内的正整数进行测试验证，并找出其中最长的序列");
    int question_Number;
    scanf("%d", &question_Number);
    if (question_Number == 1) {
        int j = 0;
        int flag = 0;
        for (int i = 1; i <= 100; i++) {
            j = jiaogu(i);
            if (j == 1) {
                printf("true\n");
            } else {
                printf("flause\n");
                flag = 1;
            }
        }
        if (flag == 0) {
            printf("100以内的正整数经过角谷猜想处理最后都为1\n");
        } else if (flag == 1) {
            printf("100以内的正整数经过角谷猜想处理最后不都为1\n");
        }
    } else if (question_Number == 2) {
        int key_Old, key_New;
        int maxlenth_Num;
        key_Old = bingbao(1);
        for (int i = 2; i < 100; i++) {
            key_New = bingbao(i);
            if (key_New > key_Old) {
                key_Old = key_New;
                maxlenth_Num = i;
            }
        }
        printf("%d处理后的序列是最长序列,总共处理了%d步\n", maxlenth_Num,
               key_Old);
        printf("%d", maxlenth_Num);
        for (int i = 1;; i++) {
            if (maxlenth_Num == 1) {
                printf("-->%d", maxlenth_Num);
                break;
            } else if (maxlenth_Num % 2 == 0) {
                maxlenth_Num = maxlenth_Num / 2;
                printf("-->%d", maxlenth_Num);
                if (maxlenth_Num == 1) {
                    break;
                }
            } else {
                maxlenth_Num = maxlenth_Num * 3 + 1;
                printf("-->%d", maxlenth_Num);
            }
        }
    }
    return 0;
}