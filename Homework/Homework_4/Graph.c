#include <stdio.h>
#include <stdlib.h>

#define VertexData char
#define EdgeData int
#define NumVertices 100
#define ElemType int
/*---------------邻接矩阵表示---------------*/
typedef struct {
    VertexData vertex[NumVertices];           // 顶点表
    EdgeData edge[NumVertices][NumVertices];  // 邻接矩阵——边表
    int n;                                    // 图的顶点数
    int e;                                    // 图的边数
} MTGraph;
/*---------------邻接表表示---------------*/
typedef struct node {   // 边表节点
    int adjvex;         // 邻接点域(下标)
    EdgeData cost;      // 边上的权值
    struct node *next;  // 下一边链接指针
} EdgeNode;
typedef struct {          // 顶点表节点
    VertexData vertex;    // 顶点数据域
    EdgeNode *firstedge;  // 边链表头指针
} VertexNode;
typedef struct {
    VertexNode vexlist[NumVertices];  // 图的邻接表
    int n;                            // 图的顶点数
    int e;                            // 图的边数
} AdjGraph;

/*---------------栈操作(非递归深度优先搜索要用到)---------------*/
typedef struct {
    ElemType element[NumVertices];  // 栈的数据域
    int top;                        // 栈顶指针
} STACK;
// 初始化栈
void InitStack(STACK *S) { S->top = -1; }
// 判断栈是否为空
int StackEmpty(STACK *S) { return S->top == -1; }
// 栈顶元素
ElemType Top(STACK *S) {
    if (StackEmpty(S)) {
        printf("栈为空\n");
    } else {
        return (S->element[S->top]);
    }
}
// 出栈
void Pop(STACK *S) {
    if (StackEmpty(S)) {
        printf("栈为空\n");
    } else {
        S->top = S->top - 1;
    }
}
// 入栈
void Push(STACK *S, ElemType x) {
    if (S->top == NumVertices - 1) {
        printf("栈满\n");
    } else {
        S->top = S->top + 1;
        S->element[S->top] = x;
    }
}
/*---------------队列操作(广度优先搜索要用到)---------------*/
typedef struct {
    ElemType element[NumVertices];  // 队列的数据域
    int front;                      // 队头指针
    int rear;                       // 队尾指针
} QUEUE;
// 初始化队列
void InitQueue(QUEUE *Q) { Q->front = Q->rear = 0; }
// 判断队列是否为空
int QueueEmpty(QUEUE *Q) {
    if (Q->front == Q->rear)
        return 1;
    else
        return 0;
}
// 出队
void DeQueue(QUEUE *Q, ElemType *x) {
    if (QueueEmpty(Q)) {
        printf("队列为空\n");
    } else {
        *x = Q->element[Q->front];
        Q->front = (Q->front + 1) % NumVertices;
    }
}
// 入队
void EnQueue(QUEUE *Q, ElemType x) {
    if ((Q->rear + 1) % NumVertices == Q->front) {
        printf("队列满\n");
    } else {
        Q->element[Q->rear] = x;
        Q->rear = (Q->rear + 1) % NumVertices;
    }
}
// 创建邻接矩阵
void CreatMTGraph(MTGraph *G) {
    printf("请输入图的顶点数和边数:\n");
    scanf("%d %d", &G->n, &G->e);     // 输入顶点数和边数
    printf("请输入图的顶点信息:\n");  // 输入顶点信息,建立顶点表
    for (int i = 0; i < G->n; i++) {
        scanf(" %c", &G->vertex[i]);
    }
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            G->edge[i][j] = 0;  // 初始化邻接矩阵
        }
    }
    printf("请输入图的边和权值:\n");
    for (int k = 0; k < G->e; k++) {  // 读入e条边,建立邻接矩阵
        int i, j, w;
        scanf("%d %d %d", &i, &j, &w);  // 输入边的两个顶点(i,j)和权值
        G->edge[i][j] = w;
    }
}
// 创建邻接表
void CreateAdjGraph(AdjGraph *G) {
    printf("请输入图的顶点数和边数:\n");
    scanf("%d %d", &G->n, &G->e);  // 输入顶点数和边数
    printf("请输入图的顶点信息:\n");
    for (int i = 0; i < G->n; i++) {          // 建立顶点表
        scanf(" %c", &G->vexlist[i].vertex);  // 输入顶点信息
        G->vexlist[i].firstedge = NULL;  // 初始化边表头指针,边表置为空表
    }
    printf("请输入图的边和权值:\n");
    for (int i = 0; i < G->e; i++) {  // 逐条边输入,建立边表
        int tail, head, weight;
        scanf("%d %d %d", &tail, &head,
              &weight);  // 输入边的两个顶点(i,j)和权值
        EdgeNode *p = (EdgeNode *)malloc(sizeof(EdgeNode));
        p->adjvex = head;
        p->cost = weight;
        p->next = G->vexlist[tail].firstedge;
        G->vexlist[tail].firstedge = p;
    }
}
// 邻接矩阵转邻接表
AdjGraph *MTGraph_To_AdjGraph(MTGraph *G) {
    AdjGraph *G2;
    G2 = (AdjGraph *)malloc(sizeof(AdjGraph));
    G2->n = G->n;  // 将邻接矩阵的顶点数赋给邻接表
    G2->e = G->e;  // 将邻接矩阵的边数赋给邻接表
    for (int i = 0; i < G->n; i++) {  // 将邻接矩阵的顶点信息赋给邻接表
        G2->vexlist[i].vertex = G->vertex[i];
        G2->vexlist[i].firstedge = NULL;
    }
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {  // 将邻接矩阵的边信息赋给邻接表
            if (G->edge[i][j] != 0) {
                EdgeNode *p = (EdgeNode *)malloc(sizeof(EdgeNode));
                p->adjvex = j;
                p->cost = G->edge[i][j];
                p->next = G2->vexlist[i].firstedge;
                G2->vexlist[i].firstedge = p;
            }
        }
    }
    return G2;
}
// 邻接表转邻接矩阵
MTGraph *AdjGraph_To_MTGraph(AdjGraph *G) {
    MTGraph *G1;
    G1 = (MTGraph *)malloc(sizeof(MTGraph));
    G1->n = G->n;  // 将邻接表的顶点数赋给邻接矩阵
    G1->e = G->e;  // 将邻接表的边数赋给邻接矩阵
    for (int i = 0; i < G->n; i++) {  // 将邻接表的顶点信息赋给邻接矩阵
        G1->vertex[i] = G->vexlist[i].vertex;
    }
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            G1->edge[i][j] = 0;
        }
    }
    for (int i = 0; i < G->n; i++) {  // 循环加入边信息
        EdgeNode *p = G->vexlist[i].firstedge;
        while (p != NULL) {  // 将邻接表的边信息赋给邻接矩阵
            G1->edge[i][p->adjvex] = p->cost;
            p = p->next;
        }
    }
    return G1;
}
// 输出邻接矩阵
void PrintMTGraph(MTGraph *G) {
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            printf("%d ", G->edge[i][j]);
        }
        printf("\n");
    }
}
// 输出邻接表
void PrintAdjGraph(AdjGraph *G) {
    for (int i = 0; i < G->n; i++) {
        printf("%c->", G->vexlist[i].vertex);
        EdgeNode *p = G->vexlist[i].firstedge;
        while (p != NULL) {
            printf("%c(%d)->", G->vexlist[p->adjvex].vertex, p->cost);
            p = p->next;
        }
        printf("NULL\n");
    }
}
// 各个顶点的入度、出度、度
void PrintDegree(AdjGraph *G) {
    int inDegree[NumVertices] = {0};   // 初始化入度数组
    int outDegree[NumVertices] = {0};  // 初始化出度数组
    int degree[NumVertices] = {0};     // 初始化度数组
    for (int i = 0; i < G->n; i++) {   // 计算各个顶点的入度
        EdgeNode *p = G->vexlist[i].firstedge;
        while (p != NULL) {
            inDegree[p->adjvex]++;
            outDegree[i]++;
            degree[i]++;
            degree[p->adjvex]++;
            p = p->next;
        }
    }
    for (int i = 0; i < G->n; i++) {
        printf("%c的入度为:%d,出度为:%d,度为:%d\n", G->vexlist[i].vertex,
               inDegree[i], outDegree[i], degree[i]);
    }
}
int dfn[NumVertices];      // 顶点编号
int bfn[NumVertices];      // 顶点编号
int visited[NumVertices];  // 记录顶点是否访问过
// 邻接矩阵的非递归深度优先搜索
void MT_DFS_NonRecursion_X(MTGraph *G, int i, int *count) {
    int j;
    STACK S;
    InitStack(&S);                        // 初始化栈
    Push(&S, i);                          // 顶点i入栈
    while (!StackEmpty(&S)) {             // 栈不空
        i = Top(&S);                      // 取栈顶元素
        Pop(&S);                          // 栈顶元素出栈
        if (!visited[i]) {                // 若顶点i未访问
            printf("%c ", G->vertex[i]);  // 访问顶点i
            visited[i] = 1;               // 标记顶点i已访问
            dfn[i] = (*count)++;          // 顶点i的编号,并递增编号
        }
        for (j = G->n - 1; j >= 0; j--) {  // 访问顶点i的所有邻接点
            if (G->edge[i][j] != 0 &&
                !visited[j]) {  // 若顶点j是顶点i的邻接点且未访问
                Push(&S, j);    // 顶点j入栈
            }
        }
    }
    printf("\n");
}
void MT_DFS_NonRecursion(MTGraph *G) {
    int count = 1;
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;  // 初始化数组
    }
    int forest = 1;
    for (int i = 0; i < G->n; i++) {
        if (!visited[i]) {
            printf("%d号森林:\n", forest++);
            MT_DFS_NonRecursion_X(G, i, &count);  // 从顶点i开始深度优先搜索
        }
    }
}
void MT_DFS_NonRecursion_NUM(MTGraph *G) {  // 输出顶点的编号
    for (int i = 0; i < G->n; i++) {
        printf("%c:%d\n", G->vertex[i], dfn[i]);
    }
}
// 邻接表的非递归深度优先搜索，从最后一个邻接点开始访问
void Adj_DFS_NonRecursion_X(AdjGraph *G, int i, int *count) {
    STACK S;
    InitStack(&S);                        // 初始化栈
    Push(&S, i);                          // 顶点i入栈
    printf("%c ", G->vexlist[i].vertex);  // 访问顶点i
    visited[i] = 1;                       // 标记顶点i已访问
    dfn[i] = (*count)++;                  // 顶点i的编号,并递增编号
    while (1) {
        EdgeNode *p = G->vexlist[i].firstedge;  // 取顶点i边表的头指针
        while (p) {
            if (!visited[p->adjvex])  // 若顶点j是顶点i的邻接点且未访问
            {
                Push(&S, p->adjvex);                          // 顶点j入栈
                printf("%c ", G->vexlist[p->adjvex].vertex);  // 访问顶点j
                visited[p->adjvex] = 1;       // 标记顶点j已访问
                dfn[p->adjvex] = (*count)++;  // 顶点j的编号,并递增编号
                i = p->adjvex;                // 顶点j成为当前顶点
                p = G->vexlist[i].firstedge;  // 取顶点j边表的头指针
            } else {
                p = p->next;  // 找下一个邻接点
            }
        }
        if (StackEmpty(&S))  // 栈空则退出
        {
            break;
        }
        i = Top(&S);  // 取栈顶元素
        Pop(&S);      // 栈顶元素出栈
    }
    printf("\n");
}
void Adj_DFS_NonRecursion(AdjGraph *G) {
    int count = 1;
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;  // 初始化数组
    }
    int forest = 1;
    for (int i = 0; i < G->n; i++) {
        if (!visited[i]) {
            printf("%d号森林:\n", forest++);
            Adj_DFS_NonRecursion_X(G, i, &count);  // 从顶点i开始深度优先搜索
        }
    }
}
void Adj_DFS_NonRecursion_NUM(AdjGraph *G) {  // 输出顶点的编号
    for (int i = 0; i < G->n; i++) {
        printf("%c:%d\n", G->vexlist[i].vertex, dfn[i]);
    }
}
// 邻接矩阵的递归深度优先搜索
void MT_DFS_Recursion_X(MTGraph *G, int i, int *count) {
    int j;
    printf("%c ", G->vertex[i]);  // 访问顶点i
    visited[i] = 1;               // 标记顶点i已访问
    dfn[i] = (*count)++;          // 顶点i的编号,并递增编号
    for (j = 0; j < G->n; j++) {  // 访问顶点i的所有邻接点
        if (G->edge[i][j] != 0 &&
            !visited[j]) {  // 若顶点j是顶点i的邻接点且未访问
            MT_DFS_Recursion_X(G, j, count);  // 从顶点j开始深度优先搜索
        }
    }
}
void MT_DFS_Recursion(MTGraph *G) {  // 主算法
    int count = 1;
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;  // 初始化数组
    }
    int forest = 1;
    for (int i = 0; i < G->n; i++) {
        if (!visited[i]) {
            printf("%d号森林:\n", forest++);
            MT_DFS_Recursion_X(G, i, &count);  // 从顶点i开始深度优先搜索
            printf("\n");
        }
    }
}
void MT_DFS_Recursion_NUM(MTGraph *G) {  // 输出顶点的编号
    for (int i = 0; i < G->n; i++) {
        printf("%c:%d\n", G->vertex[i], dfn[i]);
    }
}
// 邻接表的递归深度优先搜索
void Adj_DFS_Recursion_X(AdjGraph *G, int i, int *count) {
    EdgeNode *p;
    printf("%c ", G->vexlist[i].vertex);  // 访问顶点i
    visited[i] = 1;                       // 标记顶点i已访问
    dfn[i] = (*count)++;                  // 顶点i的编号,并递增编号
    p = G->vexlist[i].firstedge;          // 取顶点i边表的头指针
    while (p != NULL) {                   // 访问顶点i的所有邻接点
        if (!visited[p->adjvex]) {  // 若顶点j是顶点i的邻接点且未访问
            Adj_DFS_Recursion_X(G, p->adjvex,
                                count);  // 从顶点j开始深度优先搜索
        }
        p = p->next;
    }
}
void Adj_DFS_Recursion(AdjGraph *G) {  // 主算法
    int count = 1;
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;  // 初始化数组
    }
    int forest = 1;
    for (int i = 0; i < G->n; i++) {
        if (!visited[i]) {
            printf("%d号森林:\n", forest++);
            Adj_DFS_Recursion_X(G, i, &count);  // 从顶点i开始深度优先搜索
            printf("\n");
        }
    }
}
void Adj_DFS_Recursion_NUM(AdjGraph *G) {  // 输出顶点的编号
    for (int i = 0; i < G->n; i++) {
        printf("%c:%d\n", G->vexlist[i].vertex, dfn[i]);
    }
}
// 邻接矩阵的广度优先搜索
void MT_BFS_X(MTGraph *G, int i, int *count) {
    int j;
    QUEUE Q;
    InitQueue(&Q);                    // 初始化队列
    printf("%c ", G->vertex[i]);      // 访问顶点i
    visited[i] = 1;                   // 标记顶点i已访问
    dfn[i] = (*count)++;              // 顶点i的编号,并递增编号
    EnQueue(&Q, i);                   // 顶点i入队
    while (!QueueEmpty(&Q)) {         // 队列不空
        DeQueue(&Q, &i);              // 队头元素出队
        for (j = 0; j < G->n; j++) {  // 访问顶点i的所有邻接点
            if (G->edge[i][j] != 0 &&
                !visited[j]) {  // 若顶点j是顶点i的邻接点且未访问
                printf("%c ", G->vertex[j]);  // 访问顶点j
                visited[j] = 1;               // 标记顶点j已访问
                dfn[j] = (*count)++;  // 顶点j的编号,并递增编号
                EnQueue(&Q, j);       // 顶点j入队
            }
        }
    }
    printf("\n");
}
void MT_BFS(MTGraph *G) {
    int count = 1;
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;  // 初始化数组
    }
    int forest = 1;
    for (int i = 0; i < G->n; i++) {
        if (!visited[i]) {
            printf("%d号森林:\n", forest++);
            MT_BFS_X(G, i, &count);  // 从顶点i开始广度优先搜索
        }
    }
}
void MT_BFS_NUM(MTGraph *G) {  // 输出顶点的编号
    for (int i = 0; i < G->n; i++) {
        printf("%c:%d\n", G->vertex[i], dfn[i]);
    }
}
// 邻接表的广度优先搜索
void Adj_BFS_X(AdjGraph *G, int i, int *count) {
    int j;
    QUEUE Q;
    InitQueue(&Q);                        // 初始化队列
    printf("%c ", G->vexlist[i].vertex);  // 访问顶点i
    visited[i] = 1;                       // 标记顶点i已访问
    dfn[i] = (*count)++;                  // 顶点i的编号,并递增编号
    EnQueue(&Q, i);                       // 顶点i入队
    while (!QueueEmpty(&Q)) {             // 队列不空
        DeQueue(&Q, &i);                  // 队头元素出队
        EdgeNode *p = G->vexlist[i].firstedge;  // 取顶点i边表的头指针
        while (p != NULL) {             // 访问顶点i的所有邻接点
            if (!visited[p->adjvex]) {  // 若顶点j是顶点i的邻接点且未访问
                printf("%c ", G->vexlist[p->adjvex].vertex);  // 访问顶点j
                visited[p->adjvex] = 1;       // 标记顶点j已访问
                dfn[p->adjvex] = (*count)++;  // 顶点j的编号,并递增编号
                EnQueue(&Q, p->adjvex);       // 顶点j入队
            }
            p = p->next;  // 找下一个邻接点
        }
    }
    printf("\n");
}
void Adj_BFS(AdjGraph *G) {
    int count = 1;
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;  // 初始化数组
    }
    int forest = 1;
    for (int i = 0; i < G->n; i++) {
        if (!visited[i]) {
            printf("%d号森林:\n", forest++);
            Adj_BFS_X(G, i, &count);  // 从顶点i开始广度优先搜索
        }
    }
}
void Adj_BFS_NUM(AdjGraph *G) {  // 输出顶点的编号
    for (int i = 0; i < G->n; i++) {
        printf("%c:%d\n", G->vexlist[i].vertex, dfn[i]);
    }
}
int main() {
    MTGraph *G1;
    G1 = (MTGraph *)malloc(sizeof(MTGraph));
    AdjGraph *G2;
    G2 = (AdjGraph *)malloc(sizeof(AdjGraph));
    while (1) {
        int choice;
        printf("请选择图的存储方式:1.邻接矩阵;2.邻接表;0.退出\n");
        scanf("%d", &choice);
        if (choice == 1) {
            while (1) {
                int number;
                printf(
                    "请选择操作: "
                    "1.创建图的邻接矩阵;2.将邻接矩阵转邻接表;3."
                    "非递归深度优先搜索;4.递归深度优先搜索;5.广度优先搜索;0."
                    "退出\n");
                scanf("%d", &number);
                if (number == 1) {
                    CreatMTGraph(G1);
                    printf("图的邻接矩阵为:\n");
                    PrintMTGraph(G1);
                } else if (number == 2) {
                    printf("将邻接矩阵转换为邻接表:\n");
                    G2 = MTGraph_To_AdjGraph(G1);
                    PrintAdjGraph(G2);
                } else if (number == 3) {
                    printf("非递归深度优先序列:\n");
                    MT_DFS_NonRecursion(G1);
                    printf("非递归深度优先序号:\n");
                    MT_DFS_NonRecursion_NUM(G1);
                } else if (number == 4) {
                    printf("递归深度优先序列:\n");
                    MT_DFS_Recursion(G1);
                    printf("递归深度优先序号:\n");
                    MT_DFS_Recursion_NUM(G1);
                } else if (number == 5) {
                    printf("广度优先序列:\n");
                    MT_BFS(G1);
                    printf("广度优先序号:\n");
                    MT_BFS_NUM(G1);

                } else if (number == 0) {
                    break;
                }
            }
        } else if (choice == 2) {
            while (1) {
                int number;
                printf(
                    "请选择操作: "
                    "1.创建图的邻接表;2.将邻接表转邻接矩阵;3."
                    "非递归深度优先搜索;4.递归深度优先搜索;5.广度优先搜索;6."
                    "各个顶点的入度、出度、度;0."
                    "退出\n");
                scanf("%d", &number);
                if (number == 1) {
                    CreateAdjGraph(G2);
                    printf("图的邻接表为:\n");
                    PrintAdjGraph(G2);
                } else if (number == 2) {
                    printf("将邻接表转换为邻接矩阵:\n");
                    G1 = AdjGraph_To_MTGraph(G2);
                    PrintMTGraph(G1);
                } else if (number == 3) {
                    printf("非递归深度优先序列:\n");
                    Adj_DFS_NonRecursion(G2);
                    printf("非递归深度优先序号:\n");
                    Adj_DFS_NonRecursion_NUM(G2);
                } else if (number == 4) {
                    printf("递归深度优先序列:\n");
                    Adj_DFS_Recursion(G2);
                    printf("递归深度优先序号:\n");
                    Adj_DFS_Recursion_NUM(G2);
                } else if (number == 5) {
                    printf("广度优先序列:\n");
                    Adj_BFS(G2);
                    printf("广度优先序号:\n");
                    Adj_BFS_NUM(G2);
                } else if (number == 6) {
                    printf("各个顶点的入度、出度、度:\n");
                    PrintDegree(G2);
                } else if (number == 0) {
                    break;
                }
            }
        } else if (choice == 0) {
            break;
        } else {
            printf("输入错误\n");
        }
    }
    return 0;
}