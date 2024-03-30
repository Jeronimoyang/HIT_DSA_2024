// 实现线性表的链式存储结构
#include <stdio.h>
#include <stdlib.h>
#define max 100
typedef int ElemType;

typedef struct celltype {
    ElemType data;
    struct celltype *next;
} celltype;

typedef celltype *LIST;
typedef celltype *position;

// 后端插入
void end_insertion(int x, LIST rear) {
    LIST p_1 = (celltype *)malloc(sizeof(celltype));
    p_1->data = x;
    p_1->next = NULL;
    rear->next = p_1;
    // rear = rear->next;
}
// 创建线性表
LIST Input() {
    LIST p, rear;
    int n;
    int x;
    printf("计划添加多少个元素：");
    scanf("%d", &n);
    p = (celltype *)malloc(sizeof(celltype));
    p->next = NULL;
    rear = p;
    printf("请输入元素：");
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        end_insertion(x, rear);
        rear = rear->next;
    }
    return p;
    free(p);
}
// 删除给定的元素
void Delete(int p, LIST L) {
    position q, flag;
    flag = L;
    int i;
    for (i = 0; i < p - 1 && flag; i++) {
        flag = flag->next;
    }
    if (i != p - 1 || flag == NULL || flag->next == NULL) {
        printf("指定位置不存在\n");
    } else {
        q = flag->next;
        flag->next = q->next;
        free(q);
    }
}
// 删除重复的元素(有问题)
void Delete_Repetition(LIST L) {
    position q, p, temp, flag;
    int lenth, i, j;
    lenth = 0;
    q = L->next;
    flag = L->next;
    while (flag) {
        lenth++;
        flag = flag->next;
    }
    for (i = 1; i < lenth && q; i++) {
        for (j = i, p = q; j < lenth || p->next; j++) {
            if (q->data == p->next->data) {
                temp = p->next;
                p->next = temp->next;
                lenth = lenth - 1;
            } else {
                if (p) {
                    p = p->next;
                }
            }
        }
        if (q) {
            q = q->next;
        }
    }
}
// 对线性表“就地逆置”
void Inverse(LIST L) {
    position p, q;
    p = L->next;
    if (p) {
        q = p->next;
        p->next = NULL;
        while (q != NULL) {
            p = q;
            q = q->next;
            p->next = L->next;
            L->next = p;
        }
    }
}
// 线性表循环左移、右移k位
void Translation(int step, LIST L) {
    int i, j, lenth;
    lenth = 0;
    position p, q, p_1, q_1, p_2, q_2, flag_1, flag_2;
    flag_1 = L->next;
    p = L->next;
    while (p) {
        lenth++;
        if (!(p->next)) {
            flag_2 = p;
        }
        p = p->next;
    }
    if (step < 0) {
        step = -step;
        step = step % lenth;
        p_1 = L->next;
        q_1 = p_1->next;
        L->next->next = flag_2;
        for (i = 1; i < step; i++) {
            p_1 = q_1;
            q_1 = q_1->next;
            p_1->next = L->next;
            L->next = p_1;
        }
        p_2 = q_1;
        q_2 = p_2->next;
        p_2->next = NULL;
        for (i = 1; i < lenth - step; i++) {
            p_2 = q_2;
            q_2 = q_2->next;
            p_2->next = q_1;
            q_1 = p_2;
        }
        p = L->next;
        if (p) {
            q = p->next;
            p->next = NULL;
            while (q != NULL) {
                p = q;
                q = q->next;
                p->next = L->next;
                L->next = p;
            }
        }
    } else if (step > 0) {
        step = step % lenth;
        step = lenth - step;
        p_1 = L->next;
        q_1 = p_1->next;
        L->next->next = flag_2;
        for (i = 1; i < step; i++) {
            p_1 = q_1;
            q_1 = q_1->next;
            p_1->next = L->next;
            L->next = p_1;
        }
        p_2 = q_1;
        q_2 = p_2->next;
        p_2->next = NULL;
        for (i = 1; i < lenth - step; i++) {
            p_2 = q_2;
            q_2 = q_2->next;
            p_2->next = q_1;
            q_1 = p_2;
        }
        p = L->next;
        if (p) {
            q = p->next;
            p->next = NULL;
            while (q != NULL) {
                p = q;
                q = q->next;
                p->next = L->next;
                L->next = p;
            }
        }
    }
}
// 合并两个已排好序的线性表
void Merge(LIST L_1, LIST L_2) {
    position p, q, flag;
    p = L_1->next;
    q = L_2->next;
    while (p) {
        if (!(p->next)) {
            flag = p;
        }
        p = p->next;
    }
    while (q) {
        flag->next = q;
        flag = flag->next;
        q = q->next;
    }
}
// 打印线性表
void Output(LIST L) {
    position p;
    p = L->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    printf("创建一个线性表：\n");
    LIST L = Input();
    printf("当前线性表为：\n");
    Output(L);
    while (1) {
        int number;
        printf(
            "请选择要实现的功能：1.删除给定的元素；2.删除重复的元素；3."
            "对线性表“就地逆置；4.对线性表左移/"
            "右移k位；5.合并两个已排好序的线性表；0.结束操作\n");
        scanf("%d", &number);
        if (number == 1) {
            printf("当前线性表：\n");
            Output(L);
            printf("要删除第几个元素：\n");
            int local;
            scanf("%d", &local);
            Delete(local, L);
            printf("当前线性表：\n");
            Output(L);
        } else if (number == 2) {
            printf("当前线性表：\n");
            Output(L);
            Delete_Repetition(L);
            printf("当前线性表：\n");
            Output(L);
        } else if (number == 3) {
            printf("当前线性表：\n");
            Output(L);
            Inverse(L);
            printf("当前线性表：\n");
            Output(L);
        } else if (number == 4) {
            printf("当前线性表：\n");
            Output(L);
            printf("请输入移动的步长（左移为负，右移为正）：\n");
            int step;
            scanf("%d", &step);
            Translation(step, L);
            printf("当前线性表：\n");
            Output(L);
        } else if (number == 5) {
            printf("当前线性表：\n");
            Output(L);
            printf("请创建待合并的线性表：\n");
            LIST L_other = Input();
            printf("另一个线性表：\n");
            Output(L_other);
            Merge(L, L_other);
            printf("合成后的线性表：\n");
            Output(L);
        } else if (number == 0) {
            break;
        } else {
            printf("输入值非法");
        }
    }
    return 0;
    free(L);
}