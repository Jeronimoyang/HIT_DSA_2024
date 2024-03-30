// 实现线性表的顺序存储结构
#include <stdio.h>
#include <stdlib.h>
#define max 100
typedef int ElemType;
typedef int position;

// 定义线性表
typedef struct {
    ElemType elements[max];
    int last;
} LIST;
// 初始化线性表
void Initial(LIST* L) { L->last = 0; }
// 对线性表向前添加元素
void Input(LIST* L) {
    position q;
    int ele_number;
    printf("计划添加多少个元素：");
    scanf("%d", &ele_number);
    printf("开始输入元素：");
    for (q = L->last + 1; q <= ele_number; q++) {
        scanf("%d", &L->elements[q]);
        L->last = L->last + 1;
    }
}
// 删除给定的元素
void Delete(position p, LIST* L) {
    position q;
    if ((p > L->last) || (p < 1)) {
        printf("指定位置不存在\n");
    } else {
        L->last = L->last - 1;
        for (q = p; q <= L->last; q++) {
            L->elements[q] = L->elements[q + 1];
        }
    }
}
// 删除重复的元素
void Delete_Repetition(LIST* L) {
    position q, p, i;
    if (L->last > 1) {
        for (q = 1; q < L->last; q++) {
            for (p = q + 1; p <= L->last; p++) {
                if (L->elements[p] == L->elements[q]) {
                    L->last = L->last - 1;
                    for (i = p; i <= L->last; i++) {
                        L->elements[i] = L->elements[i + 1];
                    }
                    p = p - 1;
                }
            }
        }
    }
}
// 对线性表“就地逆置”
void Inverse(LIST* L) {
    int i, j, temp;
    for (i = 1, j = L->last; i < j; i++, j--) {
        temp = L->elements[i];
        L->elements[i] = L->elements[j];
        L->elements[j] = temp;
    }
}
// 线性表循环左移、右移k位
void Translation(int step, LIST* L) {
    int i, j, temp;
    if (step < 0) {
        step = -step;
        step = step % L->last;
        for (i = 1, j = step; i < j; i++, j--) {
            temp = L->elements[i];
            L->elements[i] = L->elements[j];
            L->elements[j] = temp;
        }
        for (i = step + 1, j = L->last; i < j; i++, j--) {
            temp = L->elements[i];
            L->elements[i] = L->elements[j];
            L->elements[j] = temp;
        }
        for (i = 1, j = L->last; i < j; i++, j--) {
            temp = L->elements[i];
            L->elements[i] = L->elements[j];
            L->elements[j] = temp;
        }
    } else if (step > 0) {
        step = step % L->last;
        for (i = 1, j = L->last - step; i < j; i++, j--) {
            temp = L->elements[i];
            L->elements[i] = L->elements[j];
            L->elements[j] = temp;
        }
        for (i = L->last - step + 1, j = L->last; i < j; i++, j--) {
            temp = L->elements[i];
            L->elements[i] = L->elements[j];
            L->elements[j] = temp;
        }
        for (i = 1, j = L->last; i < j; i++, j--) {
            temp = L->elements[i];
            L->elements[i] = L->elements[j];
            L->elements[j] = temp;
        }
    }
}
// 合并两个已排好序的线性表
void Merge(LIST* L_1, LIST* L_2) {
    int i, j;
    if (L_2->last > 0) {
        for (i = L_1->last + 1, j = 1; i <= L_1->last + L_2->last; i++, j++) {
            L_1->elements[i] = L_2->elements[j];
        }
    }
    L_1->last = L_1->last + L_2->last;
}
// 打印线性表
void Output(LIST* L) {
    position q;
    if (L->last == 0) {
        printf("NULL\n");
    } else {
        for (q = 1; q <= L->last; q++) {
            printf("%d ", L->elements[q]);
        }
        printf("\n");
    }
}

int main() {
    LIST L;
    Initial(&L);
    printf("创建一个线性表：\n");
    Input(&L);
    printf("当前线性表为：\n");
    Output(&L);
    while (1) {
        int number;
        printf(
            "请选择要实现的功能：1.删除给定的元素；2.删除重复的元素；3."
            "对线性表“就地逆置；4.对线性表左移/"
            "右移k位；5.合并两个已排好序的线性表；0.结束操作\n");
        scanf("%d", &number);
        if (number == 1) {
            printf("当前线性表：\n");
            Output(&L);
            printf("要删除第几个元素：");
            int local;
            scanf("%d", &local);
            Delete(local, &L);
            printf("当前线性表：\n");
            Output(&L);
        } else if (number == 2) {
            printf("当前线性表：\n");
            Output(&L);
            Delete_Repetition(&L);
            printf("当前线性表：\n");
            Output(&L);
        } else if (number == 3) {
            printf("当前线性表：\n");
            Output(&L);
            Inverse(&L);
            printf("当前线性表：\n");
            Output(&L);
        } else if (number == 4) {
            printf("当前线性表：\n");
            Output(&L);
            printf("请输入移动的步长（左移为负，右移为正）：");
            int step;
            scanf("%d", &step);
            Translation(step, &L);
            printf("当前线性表：\n");
            Output(&L);
        } else if (number == 5) {
            printf("当前线性表：\n");
            Output(&L);
            LIST L_other;
            Initial(&L_other);
            printf("请创建待合并的线性表：\n");
            Input(&L_other);
            printf("另一个线性表：\n");
            Output(&L_other);
            Merge(&L, &L_other);
            printf("合成后的线性表：\n");
            Output(&L);
        } else if (number == 0) {
            break;
        } else {
            printf("输入值非法");
        }
    }
    return 0;
}