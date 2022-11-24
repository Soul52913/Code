#include <limits.h>
#include <iostream>
#include <vector>
#include <queue>

int 

typedef enum { false, true } bool;
//查找权值最小的、尚未被选择的顶点，key 数组记录了各顶点之间的权值数据，visited数组记录着各个顶点是否已经被选择的信息
int min_Key(int key[], bool visited[])
{
    int min = 2147483647, min_index;  //遍历 key 数组使用，min 记录最小的权值，min_index 记录最小权值关联的顶点
    //遍历 key 数组
    for (int v = 0; v < V; v++) {
        //如果当前顶点为被选择，且对应的权值小于 min 值
        if (visited[v] == false && key[v] < min) {
            //更新  min 的值并记录该顶点的位置
            min = key[v];
            min_index = v;
        }
    }
    //返回最小权值的顶点的位置
    return min_index;
}

//输出最小生成树
void print_MST(int parent[], int cost[V][V])
{
    int minCost = 0;
    printf("最小生成树为：\n");
    //遍历 parent 数组
    for (int i = 1; i < V; i++) {
        //parent 数组下标值表示各个顶点，各个下标对应的值为该顶点的父节点
        printf("%d - %d wight:%d\n", parent[i] + 1, i + 1, cost[i][parent[i]]);//由于数组下标从 0 开始，因此输出时各自 +1
        //统计最小生成树的总权值
        minCost += cost[i][parent[i]];
    }
    printf("总权值为：%d", minCost);
}

//根据用户提供了图的信息（存储在 cost 数组中），寻找最小生成树
void find_MST(int cost[V][V])
{    //key 数组用于记录 B 类顶点到 A 类顶点的权值
    //parent 数组用于记录最小生成树中各个顶点父节点的位置，便于最终生成最小生成树
    //visited 数组用于记录各个顶点属于 A 类还是 B 类
    int parent[V], key[V];
    bool visited[V];

    // 初始化 3 个数组
    for (int i = 0; i < V; i++) {
        key[i] = 2147483647;    // 将 key 数组各个位置设置为无限大的数
        visited[i] = false;     // 所有的顶点全部属于 B 类
        parent[i] = -1;         // 所有顶点都没有父节点
    }
    // 选择 key 数组中第一个顶点，开始寻找最小生成树
    key[0] = 0;  // 该顶点对应的权值设为 0
    parent[0] = -1; // 该顶点没有父节点

    // 对于 V 个顶点的图，最需选择 V-1 条路径，即可构成最小生成树
    for (int x = 0; x < V - 1; x++)
    {
        // 从 key 数组中找到权值最小的顶点所在的位置
        int u = min_Key(key, visited);
        // 该顶点划分到 A 类
        visited[u] = true;

        // 由于新顶点加入 A 类，因此需要更新 key 数组中的数据
        for (int v = 0; v < V; v++)
        {
            // 如果类 B 中存在到下标为 u 的顶点的权值比 key 数组中记录的权值还小，表明新顶点的加入，使得类 B 到类 A 顶点的权值有了更好的选择
            if (cost[u][v] != 0 && visited[v] == false && cost[u][v] < key[v])
            {
                // 更新 parent 数组记录的各个顶点父节点的信息
                parent[v] = u;
                // 更新 key 数组
                key[v] = cost[u][v];
            }
        }
    }
    //根据 parent 记录的各个顶点父节点的信息，输出寻找到的最小生成树
    print_MST(parent, cost);
}

// main function
int main()
{
    int p1, p2;
    int wight;
    int cost[V][V] = { 0 };
    printf("输入图（顶点到顶点的路径和权值)：\n");
    while (1) {
        scanf("%d %d", &p1, &p2);
        //如果用户输入 -1 -1，表示输入结束
        if (p1 == -1 && p2 == -1) {
            break;
        }
        scanf("%d", &wight);
        cost[p1 - 1][p2 - 1] = wight;
        cost[p2 - 1][p1 - 1] = wight;
    }
    // 根据用户输入的图的信息，寻找最小生成树
    find_MST(cost);
    return 0;
}