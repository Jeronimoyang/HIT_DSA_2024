#include <stdio.h>
#include <stdlib.h>

#define VertexData int
#define EdgeData int
#define NumVertices 100
#define inf 99999
/*---------------邻接矩阵表示---------------*/
typedef struct {
    VertexData vertex[NumVertices];           // 顶点表
    EdgeData edge[NumVertices][NumVertices];  // 邻接矩阵——边表
    int n;                                    // 图的顶点数
    int e;                                    // 图的边数
} MTGraph;
// 创建图(从txt文件中读取)
void Create_Graph(MTGraph *G) {
    FILE *fp;
    fp = fopen("Graph.txt", "r");
    fscanf(fp, "%d", &G->n);
    fscanf(fp, "%d", &G->e);
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            G->edge[i][j] = inf;
        }
    }
    for (int i = 0; i < G->n; i++) {
        G->edge[i][i] = 0;
    }
    for (int i = 0; i < G->n; i++) {
        fscanf(fp, "%d", &G->vertex[i]);
    }
    for (int i = 0; i < G->e; i++) {
        int u, v, w;
        fscanf(fp, "%d %d %d", &u, &v, &w);
        G->edge[u][v] = w;
    }
    fclose(fp);
}
// 查找最短距离的顶点
int MinCost(MTGraph *G, int D[], int S[]) {
    int temp = inf;
    int w = 0;
    for (int i = 0; i < G->n; i++) {
        if (!S[i] && D[i] < temp) {
            temp = D[i];
            w = i;
        }
    }
    return w;
}
// Dijkstra算法
void Dijkstra(MTGraph *G, int source, int D[], int P[], int S[]) {
    for (int i = 0; i < G->n; i++) {
        D[i] = G->edge[source][i];
        P[i] = source;
        S[i] = 0;
    }
    S[source] = 1;
    for (int i = 0; i < G->n - 1; i++) {
        int w = MinCost(G, D, S);
        S[w] = 1;
        for (int v = 0; v < G->n; v++) {
            if (!S[v]) {
                int sum = D[w] + G->edge[w][v];
                if (sum < D[v]) {
                    D[v] = sum;
                    P[v] = w;
                }
            }
        }
    }
}
// 打印Dijkstra算法的最短路径(给定源点，打印源点到其他顶点的最短路径和长度)例如:源点为1，目标点为2，输出为2<-1
void Print_Dijkstra(MTGraph *G, int source, int D[], int P[]) {
    for (int i = 0; i < G->n; i++) {
        if (i != source) {
            printf("源点%d到顶点%d:", source, i);
            if (D[i] != inf) {
                printf("最短路径为:");
                printf("%d", i);
                int k = P[i];
                while (k != source) {
                    printf("<-%d", k);
                    k = P[k];
                }
                printf("<-%d  最短路径长度为:%d\n", source, D[i]);
            } else {
                printf("无最短路径\n");
            }
        }
    }
}
// Floyd算法
void Floyd(MTGraph *G, int D[][NumVertices], int P[][NumVertices]) {
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            D[i][j] = G->edge[i][j];
            P[i][j] = -1;
        }
    }
    for (int k = 0; k < G->n; k++) {
        for (int i = 0; i < G->n; i++) {
            for (int j = 0; j < G->n; j++) {
                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k;
                }
            }
        }
    }
}
// 递归查找路径
void Path(int i, int j, int P[][NumVertices]) {
    int k = P[i][j];
    if (k != -1) {
        Path(i, k, P);
        printf("%d->", k);
        Path(k, j, P);
    }
}
// 打印Floyd算法的最短路径(打印最短距离矩阵、最短路径矩阵和任意两点之间的最短路径和长度)
void Print_Floyd(MTGraph *G, int D[][NumVertices], int P[][NumVertices]) {
    printf("最短路径长度矩阵为:\n");
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            if (D[i][j] == inf) {
                printf("   inf ");
            } else {
                printf("%4d ", D[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("最短路径矩阵为:\n");
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            printf("%4d ", P[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            if (i != j) {
                printf("源点%d到顶点%d:", i, j);
                if (D[i][j] != inf) {
                    printf("最短路径为:");
                    printf("%d->", i);
                    Path(i, j, P);
                    printf("%d  最短路径长度为:%d\n", j, D[i][j]);
                } else {
                    printf("无最短路径\n");
                }
            }
        }
    }
}
// 利用Floyd-Warshall算法解决单目标最短路径问题(给定目标点，打印源点到目标点的最短路径和长度)
void Single_Target(MTGraph *G, int D[][NumVertices], int P[][NumVertices]) {
    int target;
    printf("请输入目标点:");
    scanf("%d", &target);
    for (int i = 0; i < G->n; i++) {
        if (i != target) {
            printf("源点%d到目标点%d:", i, target);
            if (D[i][target] != inf) {
                printf("最短路径为:");
                printf("%d->", i);
                Path(i, target, P);
                printf("%d  最短路径长度为:%d\n", target, D[i][target]);
            } else {
                printf("无最短路径\n");
            }
        }
    }
}
// 利用Floyd-Warshall算法解决单顶点对间最短路径问题(给定两个顶点，打印两个顶点之间的最短路径和长度)
void Single_Pair(MTGraph *G, int D[][NumVertices], int P[][NumVertices]) {
    int u, v;
    printf("请输入两个顶点:");
    scanf("%d %d", &u, &v);
    printf("源点%d到顶点%d:", u, v);
    if (D[u][v] != inf) {
        printf("最短路径为:");
        printf("%d->", u);
        Path(u, v, P);
        printf("%d  最短路径长度为:%d\n", v, D[u][v]);
    } else {
        printf("无最短路径\n");
    }
    printf("源点%d到顶点%d:", v, u);
    if (D[v][u] != inf) {
        printf("最短路径为:");
        printf("%d->", v);
        Path(v, u, P);
        printf("%d  最短路径长度为:%d\n", u, D[v][u]);
    } else {
        printf("无最短路径\n");
    }
}
int main() {
    while (1) {
        int function_option;
        printf(
            "请选择功能实现:\n1.实现单源最短路径的Dijkstra算法;\n2."
            "实现全局最短路径的Floyd-Warshall算法;\n3.利用Floyd-"
            "Warshall算法解决单目标最短路径问题;\n4.利用Floyd-"
            "Warshall算法解决单顶点对间最短路径问题;\n0.退出\n");
        scanf("%d", &function_option);
        if (function_option == 1) {
            MTGraph *G = (MTGraph *)malloc(sizeof(MTGraph));
            Create_Graph(G);
            int D[NumVertices];  // 源点1到源点i的当前最短路径长度
            int P[NumVertices];  // 源点1到源点i的当前最短路径上，最后经过的顶点
            int S[NumVertices];  // 存放源点和已生成的终点，实际上是bool类型
            int source;
            printf("请输入源点:");
            scanf("%d", &source);
            Dijkstra(G, source, D, P, S);
            Print_Dijkstra(G, source, D, P);
        } else if (function_option == 2) {
            MTGraph *G = (MTGraph *)malloc(sizeof(MTGraph));
            Create_Graph(G);
            int D[NumVertices][NumVertices];  // 最短路径长度矩阵
            int P[NumVertices][NumVertices];  // 最短路径矩阵
            Floyd(G, D, P);
            Print_Floyd(G, D, P);
        } else if (function_option == 3) {
            MTGraph *G = (MTGraph *)malloc(sizeof(MTGraph));
            Create_Graph(G);
            int D[NumVertices][NumVertices];  // 最短路径长度矩阵
            int P[NumVertices][NumVertices];  // 最短路径矩阵
            Floyd(G, D, P);
            Single_Target(G, D, P);
        } else if (function_option == 4) {
            MTGraph *G = (MTGraph *)malloc(sizeof(MTGraph));
            Create_Graph(G);
            int D[NumVertices][NumVertices];  // 最短路径长度矩阵
            int P[NumVertices][NumVertices];  // 最短路径矩阵
            Floyd(G, D, P);
            Single_Pair(G, D, P);
        } else if (function_option == 0) {
            break;
        } else {
            printf("输入错误，请重新输入\n");
        }
    }
    return 0;
}