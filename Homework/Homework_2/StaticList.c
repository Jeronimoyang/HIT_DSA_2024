// 实现线性表的静态单向链表存储结构
#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
#define maxsize 100

typedef struct StaticList {
    ElemType data;
    int next;
} spacestr;

spacestr SPACE[maxsize];
typedef int position, Cursor;
Cursor L, M, av;

// 可用空间初始化
void Initialize(int number) {
    int j;
    for (j = 0; j < number - 1; j++) {
        SPACE[j].next = j + 1;
    }
    SPACE[j].next = -1;
    av = 0;
}
// 添加元素
void Input(int number) {
    Cursor p = av;
    printf("请输入元素：\n");
    for (int i = 1; i <= number; i++) {
        scanf("%d", &SPACE[p].data);
        p = SPACE[p].next;
    }
}
// 实现线性表“就地逆置”
Cursor Inverse() {
    Cursor p, q;
    p = av;
    q = -1;
    while (p != -1) {
        p = SPACE[av].next;
        SPACE[av].next = q;
        q = av;
        av = p;
    }
    return q;
}
// 打印线性表
void Output() {
    Cursor p = av;
    while (p != -1) {
        printf("%d ", SPACE[p].data);
        p = SPACE[p].next;
    }
    printf("\n");
}

int main() {
    printf("要添加多少个元素：");
    int number;
    scanf("%d", &number);
    Initialize(number);
    Input(number);
    printf("当前线性表：\n");
    Output();
    av = Inverse();
    printf("就地逆置后的线性表：\n");
    Output();
    return 0;
}