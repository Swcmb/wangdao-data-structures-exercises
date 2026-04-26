#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
#define INF 999999

typedef int ElemType;

// 邻接矩阵
typedef struct{
    int n, e; // 顶点数和边数
    int edges[MaxSize][MaxSize]; // 邻接矩阵
    ElemType vertex[MaxSize]; // 顶点信息
}MGraph;

// 初始化邻接矩阵
void InitMGraph(MGraph &G, int n){
    G.n = n;
    G.e = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i == j){
                G.edges[i][j] = 0;
            }else{
                G.edges[i][j] = INF;
            }
        }
    }
}

// 添加边
void AddEdge(MGraph &G, int u, int v, int w){
    G.edges[u][v] = w;
    G.edges[v][u] = w; // 无向图
    G.e++;
}

// 邻接表
typedef struct ArcNode{
    int adjvex;
    int weight;
    struct ArcNode *next;
}ArcNode;

typedef struct VNode{
    ElemType data;
    ArcNode *firstarc;
}VNode, AdjList[MaxSize];

typedef struct{
    AdjList vertices;
    int n, e;
}ALGraph;

// 初始化邻接表
void InitALGraph(ALGraph &G, int n){
    G.n = n;
    G.e = 0;
    for(int i=0; i<n; i++){
        G.vertices[i].firstarc = NULL;
    }
}

// 添加边
void AddEdgeAL(ALGraph &G, int u, int v, int w){
    ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
    p->adjvex = v;
    p->weight = w;
    p->next = G.vertices[u].firstarc;
    G.vertices[u].firstarc = p;
    
    // 无向图
    p = (ArcNode *)malloc(sizeof(ArcNode));
    p->adjvex = u;
    p->weight = w;
    p->next = G.vertices[v].firstarc;
    G.vertices[v].firstarc = p;
    
    G.e++;
}

// 访问标记数组
int visited[MaxSize];

// 深度优先遍历（邻接矩阵）
void DFS_M(MGraph G, int v){
    printf("%d ", v);
    visited[v] = 1;
    for(int i=0; i<G.n; i++){
        if(G.edges[v][i] != 0 && G.edges[v][i] != INF && !visited[i]){
            DFS_M(G, i);
        }
    }
}

// 深度优先遍历（邻接表）
void DFS_AL(ALGraph G, int v){
    printf("%d ", v);
    visited[v] = 1;
    ArcNode *p = G.vertices[v].firstarc;
    while(p != NULL){
        if(!visited[p->adjvex]){
            DFS_AL(G, p->adjvex);
        }
        p = p->next;
    }
}

// 广度优先遍历（邻接矩阵）
void BFS_M(MGraph G, int v){
    int queue[MaxSize], front=0, rear=0;
    printf("%d ", v);
    visited[v] = 1;
    queue[rear++] = v;
    while(front < rear){
        int u = queue[front++];
        for(int i=0; i<G.n; i++){
            if(G.edges[u][i] != 0 && G.edges[u][i] != INF && !visited[i]){
                printf("%d ", i);
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

// 广度优先遍历（邻接表）
void BFS_AL(ALGraph G, int v){
    int queue[MaxSize], front=0, rear=0;
    printf("%d ", v);
    visited[v] = 1;
    queue[rear++] = v;
    while(front < rear){
        int u = queue[front++];
        ArcNode *p = G.vertices[u].firstarc;
        while(p != NULL){
            if(!visited[p->adjvex]){
                printf("%d ", p->adjvex);
                visited[p->adjvex] = 1;
                queue[rear++] = p->adjvex;
            }
            p = p->next;
        }
    }
}

// Prim算法求最小生成树
void Prim(MGraph G, int start){
    int lowcost[MaxSize]; // 记录当前生成树到各顶点的最小权值
    int closest[MaxSize]; // 记录当前生成树中与各顶点最近的顶点
    int sum = 0;
    
    for(int i=0; i<G.n; i++){
        lowcost[i] = G.edges[start][i];
        closest[i] = start;
    }
    lowcost[start] = 0;
    
    for(int i=1; i<G.n; i++){
        int min = INF, k = -1;
        for(int j=0; j<G.n; j++){
            if(lowcost[j] != 0 && lowcost[j] < min){
                min = lowcost[j];
                k = j;
            }
        }
        if(k == -1) break;
        printf("边(%d,%d) 权值:%d\n", closest[k], k, min);
        sum += min;
        lowcost[k] = 0;
        
        for(int j=0; j<G.n; j++){
            if(lowcost[j] != 0 && G.edges[k][j] < lowcost[j]){
                lowcost[j] = G.edges[k][j];
                closest[j] = k;
            }
        }
    }
    printf("最小生成树总权值: %d\n", sum);
}

// Kruskal算法求最小生成树
typedef struct Edge{
    int u, v, w;
}Edge;

// 排序边
void SortEdges(Edge edges[], int e){
    for(int i=0; i<e-1; i++){
        for(int j=0; j<e-i-1; j++){
            if(edges[j].w > edges[j+1].w){
                Edge temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }
}

// 并查集查找
int Find(int parent[], int x){
    while(parent[x] != x){
        x = parent[x];
    }
    return x;
}

// Kruskal算法
void Kruskal(MGraph G){
    Edge edges[MaxSize];
    int k = 0;
    for(int i=0; i<G.n; i++){
        for(int j=i+1; j<G.n; j++){
            if(G.edges[i][j] != 0 && G.edges[i][j] != INF){
                edges[k].u = i;
                edges[k].v = j;
                edges[k].w = G.edges[i][j];
                k++;
            }
        }
    }
    SortEdges(edges, G.e);
    
    int parent[MaxSize];
    for(int i=0; i<G.n; i++){
        parent[i] = i;
    }
    
    int sum = 0, count = 0;
    for(int i=0; i<G.e; i++){
        int u = Find(parent, edges[i].u);
        int v = Find(parent, edges[i].v);
        if(u != v){
            printf("边(%d,%d) 权值:%d\n", edges[i].u, edges[i].v, edges[i].w);
            sum += edges[i].w;
            parent[v] = u;
            count++;
            if(count == G.n - 1) break;
        }
    }
    printf("最小生成树总权值: %d\n", sum);
}

// Dijkstra算法求最短路径
void Dijkstra(MGraph G, int start){
    int dist[MaxSize]; // 记录到各顶点的最短距离
    int path[MaxSize]; // 记录最短路径的前驱
    int s[MaxSize]; // 标记是否已加入集合
    
    for(int i=0; i<G.n; i++){
        dist[i] = G.edges[start][i];
        if(dist[i] < INF){
            path[i] = start;
        }else{
            path[i] = -1;
        }
        s[i] = 0;
    }
    s[start] = 1;
    dist[start] = 0;
    
    for(int i=1; i<G.n; i++){
        int min = INF, k = -1;
        for(int j=0; j<G.n; j++){
            if(!s[j] && dist[j] < min){
                min = dist[j];
                k = j;
            }
        }
        if(k == -1) break;
        s[k] = 1;
        
        for(int j=0; j<G.n; j++){
            if(!s[j] && dist[j] > dist[k] + G.edges[k][j]){
                dist[j] = dist[k] + G.edges[k][j];
                path[j] = k;
            }
        }
    }
    
    for(int i=0; i<G.n; i++){
        if(i != start){
            printf("到顶点%d的最短距离: %d, 路径: ", i, dist[i]);
            int j = i;
            while(j != start){
                printf("%d <- ", j);
                j = path[j];
            }
            printf("%d\n", start);
        }
    }
}

// Floyd算法求最短路径
void Floyd(MGraph G){
    int dist[MaxSize][MaxSize];
    int path[MaxSize][MaxSize];
    
    for(int i=0; i<G.n; i++){
        for(int j=0; j<G.n; j++){
            dist[i][j] = G.edges[i][j];
            if(dist[i][j] < INF){
                path[i][j] = i;
            }else{
                path[i][j] = -1;
            }
        }
    }
    
    for(int k=0; k<G.n; k++){
        for(int i=0; i<G.n; i++){
            for(int j=0; j<G.n; j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
    
    for(int i=0; i<G.n; i++){
        for(int j=0; j<G.n; j++){
            if(i != j){
                printf("%d到%d的最短距离: %d, 路径: ", i, j, dist[i][j]);
                int k = j;
                while(k != i){
                    printf("%d <- ", k);
                    k = path[i][k];
                }
                printf("%d\n", i);
            }
        }
    }
}

// 拓扑排序
bool TopologicalSort(ALGraph G){
    int indegree[MaxSize] = {0};
    int queue[MaxSize], front=0, rear=0;
    int count = 0;
    
    // 计算入度
    for(int i=0; i<G.n; i++){
        ArcNode *p = G.vertices[i].firstarc;
        while(p != NULL){
            indegree[p->adjvex]++;
            p = p->next;
        }
    }
    
    // 入度为0的顶点入队
    for(int i=0; i<G.n; i++){
        if(indegree[i] == 0){
            queue[rear++] = i;
        }
    }
    
    while(front < rear){
        int u = queue[front++];
        printf("%d ", u);
        count++;
        
        ArcNode *p = G.vertices[u].firstarc;
        while(p != NULL){
            int v = p->adjvex;
            indegree[v]--;
            if(indegree[v] == 0){
                queue[rear++] = v;
            }
            p = p->next;
        }
    }
    
    printf("\n");
    return count == G.n;
}

// 关键路径
void CriticalPath(ALGraph G){
    int ve[MaxSize], vl[MaxSize];
    int queue[MaxSize], front=0, rear=0;
    
    // 初始化ve
    for(int i=0; i<G.n; i++){
        ve[i] = 0;
    }
    
    // 拓扑排序
    int indegree[MaxSize] = {0};
    for(int i=0; i<G.n; i++){
        ArcNode *p = G.vertices[i].firstarc;
        while(p != NULL){
            indegree[p->adjvex]++;
            p = p->next;
        }
    }
    for(int i=0; i<G.n; i++){
        if(indegree[i] == 0){
            queue[rear++] = i;
        }
    }
    
    while(front < rear){
        int u = queue[front++];
        ArcNode *p = G.vertices[u].firstarc;
        while(p != NULL){
            int v = p->adjvex;
            if(ve[v] < ve[u] + p->weight){
                ve[v] = ve[u] + p->weight;
            }
            indegree[v]--;
            if(indegree[v] == 0){
                queue[rear++] = v;
            }
            p = p->next;
        }
    }
    
    // 初始化vl
    for(int i=0; i<G.n; i++){
        vl[i] = ve[G.n-1];
    }
    
    // 逆拓扑排序
    int stack[MaxSize], top=0;
    int outdegree[MaxSize] = {0};
    for(int i=0; i<G.n; i++){
        ArcNode *p = G.vertices[i].firstarc;
        while(p != NULL){
            outdegree[i]++;
            p = p->next;
        }
    }
    for(int i=0; i<G.n; i++){
        if(outdegree[i] == 0){
            stack[top++] = i;
        }
    }
    
    while(top > 0){
        int u = stack[--top];
        ArcNode *p = G.vertices[u].firstarc;
        while(p != NULL){
            int v = p->adjvex;
            if(vl[u] > vl[v] - p->weight){
                vl[u] = vl[v] - p->weight;
            }
            outdegree[u]--;
            if(outdegree[u] == 0){
                stack[top++] = u;
            }
            p = p->next;
        }
    }
    
    // 计算ee和el
    for(int u=0; u<G.n; u++){
        ArcNode *p = G.vertices[u].firstarc;
        while(p != NULL){
            int v = p->adjvex;
            int ee = ve[u];
            int el = vl[v] - p->weight;
            if(ee == el){
                printf("关键活动: %d->%d\n", u, v);
            }
            p = p->next;
        }
    }
}

// 打印邻接矩阵
void PrintMGraph(MGraph G){
    printf("邻接矩阵:\n");
    for(int i=0; i<G.n; i++){
        for(int j=0; j<G.n; j++){
            if(G.edges[i][j] == INF){
                printf("∞ ");
            }else{
                printf("%d ", G.edges[i][j]);
            }
        }
        printf("\n");
    }
}

// 打印邻接表
void PrintALGraph(ALGraph G){
    printf("邻接表:\n");
    for(int i=0; i<G.n; i++){
        printf("%d: ", i);
        ArcNode *p = G.vertices[i].firstarc;
        while(p != NULL){
            printf("%d(%d) ", p->adjvex, p->weight);
            p = p->next;
        }
        printf("\n");
    }
}

int main(){
    // 测试邻接矩阵
    printf("=== 邻接矩阵 ===\n");
    MGraph G;
    InitMGraph(G, 5);
    AddEdge(G, 0, 1, 10);
    AddEdge(G, 0, 2, 5);
    AddEdge(G, 1, 2, 2);
    AddEdge(G, 1, 3, 1);
    AddEdge(G, 2, 1, 3);
    AddEdge(G, 2, 3, 9);
    AddEdge(G, 2, 4, 2);
    AddEdge(G, 3, 4, 4);
    AddEdge(G, 4, 0, 7);
    AddEdge(G, 4, 3, 6);
    PrintMGraph(G);
    
    // 测试邻接表
    printf("\n=== 邻接表 ===\n");
    ALGraph AG;
    InitALGraph(AG, 5);
    AddEdgeAL(AG, 0, 1, 10);
    AddEdgeAL(AG, 0, 2, 5);
    AddEdgeAL(AG, 1, 2, 2);
    AddEdgeAL(AG, 1, 3, 1);
    AddEdgeAL(AG, 2, 3, 9);
    AddEdgeAL(AG, 2, 4, 2);
    AddEdgeAL(AG, 3, 4, 4);
    PrintALGraph(AG);
    
    // 测试DFS
    printf("\n=== 深度优先遍历 ===\n");
    memset(visited, 0, sizeof(visited));
    printf("邻接矩阵DFS: ");
    DFS_M(G, 0);
    printf("\n");
    memset(visited, 0, sizeof(visited));
    printf("邻接表DFS: ");
    DFS_AL(AG, 0);
    printf("\n");
    
    // 测试BFS
    printf("\n=== 广度优先遍历 ===\n");
    memset(visited, 0, sizeof(visited));
    printf("邻接矩阵BFS: ");
    BFS_M(G, 0);
    printf("\n");
    memset(visited, 0, sizeof(visited));
    printf("邻接表BFS: ");
    BFS_AL(AG, 0);
    printf("\n");
    
    // 测试最小生成树
    printf("\n=== 最小生成树 ===\n");
    printf("Prim算法:\n");
    Prim(G, 0);
    printf("Kruskal算法:\n");
    Kruskal(G);
    
    // 测试最短路径
    printf("\n=== 最短路径 ===\n");
    printf("Dijkstra算法:\n");
    Dijkstra(G, 0);
    printf("Floyd算法:\n");
    Floyd(G);
    
    // 测试拓扑排序
    printf("\n=== 拓扑排序 ===\n");
    ALGraph DG;
    InitALGraph(DG, 6);
    AddEdgeAL(DG, 0, 1, 1);
    AddEdgeAL(DG, 0, 2, 1);
    AddEdgeAL(DG, 1, 3, 1);
    AddEdgeAL(DG, 2, 3, 1);
    AddEdgeAL(DG, 2, 4, 1);
    AddEdgeAL(DG, 3, 5, 1);
    AddEdgeAL(DG, 4, 5, 1);
    printf("拓扑排序结果: ");
    TopologicalSort(DG);
    
    return 0;
}