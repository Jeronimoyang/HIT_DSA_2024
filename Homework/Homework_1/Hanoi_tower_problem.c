#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int key = 0;

// 汉诺塔递归
void hannuota(int num, char begin, char middle, char end) {
    if (num == 1) {
        printf("%c-->%c\n", begin, end);
        key++;
    } else {
        hannuota(num - 1, begin, end, middle);
        hannuota(1, begin, middle, end);
        hannuota(num - 1, middle, begin, end);
    }
}

int main() {
    int num;
    clock_t start, end;
    printf("请输入初始柱子上的圈子个数：");
    scanf("%d", &num);
    start = clock();
    hannuota(num, 'A', 'B', 'C');
    end = clock();
    printf("共需要%d步\n", key);
    printf("总用时%lf秒", (double)(end - start) / CLK_TCK);
    return 0;
}