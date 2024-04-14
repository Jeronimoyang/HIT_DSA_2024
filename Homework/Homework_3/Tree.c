#include <stdio.h>
#include <stdlib.h>
#define datatype char
#define MAX 100
#define ElemType BTREE
typedef struct node *BTREE;
// 建立二叉树的动态链表存储结构
struct node {
    BTREE lchild;
    BTREE rchild;
    datatype data;
};
// 建立栈
typedef struct {
    ElemType elements[MAX];
    int top;
} STACK;
// 建立队列
typedef struct {
    int front;
    int rear;
    ElemType elements[MAX];
} QUEUE;
// 栈函数
void Stack_MakeNull(STACK *S);          // 栈的初始化
int Stack_Empty(STACK S);               // 判断栈是否为空
void Stack_Top(ElemType *x, STACK S);   // 求栈顶元素
void Stack_Pop(ElemType *x, STACK *S);  // 出栈
void Stack_Push(ElemType x, STACK *S);  // 进栈
// 队列函数
int Queue_Addone(int i);              // 将队列位置按模加1
void Queue_MakeNull(QUEUE *Q);        // 队列的初始化
int Queue_Empty(QUEUE Q);             // 判断队列是否为空
void EnQueue(ElemType x, QUEUE *Q);   // 进队
void DeQueue(ElemType *x, QUEUE *Q);  // 出队
// 树函数
BTREE CreateBT();                     // 先序序列存储二叉树
void PrintBT(BTREE T);                // 打印二叉树
void PreOrder(BTREE T);               // 先序遍历的非递归算法
void InOrder(BTREE T);                // 中序遍历的非递归算法
void PostOrder(BTREE T);              // 后序遍历的非递归算法
void PreOrder_Recursion(BTREE T);     // 先序遍历的递归算法
void InOrder_Recursion(BTREE T);      // 中序遍历的递归算法
void PostOrder_Recursion(BTREE T);    // 后序遍历的递归算法
void LeverOrder(BTREE T);             // 层序遍历算法
int Check_Complete(BTREE T);          // 判断是否为完全二叉树
int Width(BTREE T);                   // 计算二叉树宽度
int Width_level(BTREE T, int level);  // 计算每层的宽度
int Hight(BTREE T);                   // 计算二叉树高度
// 各函数实现
void Stack_MakeNull(STACK *S) { S->top = -1; }
int Stack_Empty(STACK S) {
    if (S.top < 0) {
        return 1;
    } else {
        return 0;
    }
}
void Stack_Top(ElemType *x, STACK S) {
    if (Stack_Empty(S)) {
        printf("栈空\n");
    } else {
        *x = S.elements[S.top];
    }
}
void Stack_Pop(ElemType *x, STACK *S) {
    if (Stack_Empty(*S)) {
        printf("栈空\n");
    } else {
        *x = S->elements[S->top];
        S->top = S->top - 1;
    }
}
void Stack_Push(ElemType x, STACK *S) {
    if (S->top == MAX - 1) {
        printf("栈满\n");
    } else {
        S->top = S->top + 1;
        S->elements[S->top] = x;
    }
}
int Queue_Addone(int i) { return ((i + 1) % MAX); }
void Queue_MakeNull(QUEUE *Q) {
    Q->front = 0;
    Q->rear = 0;
}
int Queue_Empty(QUEUE Q) {
    if (Q.front == Q.rear) {
        return 1;
    } else {
        return 0;
    }
}
void EnQueue(ElemType x, QUEUE *Q) {
    if (Queue_Addone(Q->rear) == Q->front) {
        printf("队列已满\n");
    } else {
        Q->elements[Q->rear] = x;
        Q->rear = Queue_Addone(Q->rear);
    }
}
void DeQueue(ElemType *x, QUEUE *Q) {
    if (Queue_Empty(*Q)) {
        printf("队列已空\n");
    } else {
        *x = Q->elements[Q->front];
        Q->front = Queue_Addone(Q->front);
    }
}
BTREE CreateBT() {
    datatype ch;
    BTREE T = (BTREE)malloc(sizeof(struct node));
    ch = getchar();
    if (ch == '#') {
        T = NULL;
    } else {
        T->data = ch;
        T->lchild = CreateBT();
        T->rchild = CreateBT();
    }
    return T;
}
void PrintBT(BTREE T) {
    if (T != NULL) {
        printf("%c", T->data);
        printf("[");
        PrintBT(T->lchild);
        printf(",");
        PrintBT(T->rchild);
        printf("]");
    } else {
        printf("#");
    }
}
void PreOrder(BTREE T) {
    STACK S;
    Stack_MakeNull(&S);
    BTREE p;
    p = T;
    while (p != NULL || !Stack_Empty(S)) {
        while (p != NULL) {
            printf("%c", p->data);
            Stack_Push(p, &S);
            p = p->lchild;
        }
        if (!Stack_Empty(S)) {
            Stack_Pop(&p, &S);
            p = p->rchild;
        }
    }
}
void InOrder(BTREE T) {
    STACK S;
    Stack_MakeNull(&S);
    BTREE p;
    p = T;
    while (p != NULL || !Stack_Empty(S)) {
        while (p != NULL) {
            Stack_Push(p, &S);
            p = p->lchild;
        }
        if (!Stack_Empty(S)) {
            Stack_Pop(&p, &S);
            printf("%c", p->data);
            p = p->rchild;
        }
    }
}
void PostOrder(BTREE T) {
    STACK S;
    Stack_MakeNull(&S);
    BTREE p;
    BTREE flag;
    flag = NULL;
    p = T;
    while (p != NULL || !Stack_Empty(S)) {
        while (p != NULL) {
            Stack_Push(p, &S);
            p = p->lchild;
        }
        Stack_Top(&p, S);
        if (p->rchild != NULL && p->rchild != flag) {
            p = p->rchild;
        } else {
            Stack_Pop(&p, &S);
            printf("%c", p->data);
            flag = p;
            p = NULL;
        }
    }
}
void PreOrder_Recursion(BTREE T) {
    if (T != NULL) {
        printf("%c", T->data);
        PreOrder_Recursion(T->lchild);
        PreOrder_Recursion(T->rchild);
    }
}
void InOrder_Recursion(BTREE T) {
    if (T != NULL) {
        InOrder_Recursion(T->lchild);
        printf("%c", T->data);
        InOrder_Recursion(T->rchild);
    }
}
void PostOrder_Recursion(BTREE T) {
    if (T != NULL) {
        PostOrder_Recursion(T->lchild);
        PostOrder_Recursion(T->rchild);
        printf("%c", T->data);
    }
}
void LeverOrder(BTREE T) {
    QUEUE Q;
    Queue_MakeNull(&Q);
    BTREE p;
    if (T == NULL) {
        return;
    }
    EnQueue(T, &Q);
    while (!Queue_Empty(Q)) {
        DeQueue(&p, &Q);
        printf("%c", p->data);
        if (p->lchild != NULL) {
            EnQueue(p->lchild, &Q);
        }
        if (p->rchild != NULL) {
            EnQueue(p->rchild, &Q);
        }
    }
}
int Check_Complete(BTREE T) {
    QUEUE Q;
    Queue_MakeNull(&Q);
    if (T == NULL) {
        return 1;
    }
    EnQueue(T, &Q);
    BTREE p;
    while (!Queue_Empty(Q)) {
        DeQueue(&p, &Q);
        if (p->lchild != NULL && p->rchild != NULL) {
            EnQueue(p->lchild, &Q);
            EnQueue(p->rchild, &Q);
        } else if (p->lchild == NULL && p->rchild != NULL) {
            return 0;
        } else {
            if (p->lchild != NULL && p->rchild == NULL) {
                EnQueue(p->lchild, &Q);
            }
            while (!Queue_Empty(Q)) {
                DeQueue(&p, &Q);
                if (p->lchild != NULL || p->rchild != NULL) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
int Hight(BTREE T) {
    int hl, hr;
    if (T != NULL) {
        hl = Hight(T->lchild);
        hr = Hight(T->rchild);
        return ((hl > hr) ? (hl + 1) : (hr + 1));
    } else {
        return 0;
    }
}
int Width_level(BTREE T, int level) {
    if (T == NULL) {
        return 0;
    } else {
        if (level == 1) {
            return 1;
        } else {
            level = Width_level(T->lchild, level - 1) +
                    Width_level(T->rchild, level - 1);
        }
    }
    return level;
}
int Width(BTREE T) {
    int width, i;
    int width_array[100] = {0};
    if (T == NULL) {
        return 0;
    }
    for (i = 0; i < Hight(T); i++) {
        width_array[i] = Width_level(T, i + 1);
    }
    i = 0;
    while (width_array[i]) {
        if (width_array[i] > width) {
            width = width_array[i];
        }
        i++;
    }
    return width;
}
// 主函数
int main() {
    BTREE TREE;
    printf("请按先序序列输入一个二叉树:\n");
    TREE = CreateBT();
    printf("这个二叉树为:\n");
    PrintBT(TREE);
    printf("\n");
    printf("以先序遍历的非递归算法打印二叉树:\n");
    PreOrder(TREE);
    printf("\n");
    printf("以中序遍历的非递归算法打印二叉树:\n");
    InOrder(TREE);
    printf("\n");
    printf("以后序遍历的非递归算法打印二叉树:\n");
    PostOrder(TREE);
    printf("\n");
    printf("以先序遍历的递归算法打印二叉树:\n");
    PreOrder_Recursion(TREE);
    printf("\n");
    printf("以中序遍历的递归算法打印二叉树:\n");
    InOrder_Recursion(TREE);
    printf("\n");
    printf("以后序遍历的递归算法打印二叉树:\n");
    PostOrder_Recursion(TREE);
    printf("\n");
    printf("以层序遍历算法打印二叉树:\n");
    LeverOrder(TREE);
    printf("\n");
    if (Check_Complete(TREE)) {
        printf("这个二叉树是完全二叉树\n");
    } else {
        printf("这个二叉树不是完全二叉树\n");
    }
    printf("计算二叉树的高度:\n");
    printf("%d\n", Hight(TREE));
    printf("计算二叉树的宽度:\n");
    printf("%d\n", Width(TREE));
    return 0;
}