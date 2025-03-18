#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*1.图遍历就是多叉树遍历，多叉树遍历就是树遍历，树遍历就是dfs或bfs,不过图较树可能有环，如果有环，就需要使用visited数组
2.dfs相较回溯的差别：*/
// void backtrack(...)
// {
//     if (当前搜索到一个解)
//         return;

//     for (int i = 0; i < ...; i++)
//     {
//         做选择
//         ...

//
//         backtrack(...);

//         撤销刚才做的选择
//         ...
//     }
// }
struct MultiTreeNode
{
    int val;
    vector<MultiTreeNode *> childrens;
};
void traverse(MultiTreeNode *root, vector<int> &onPath)
{
    if (root == nullptr)
    {
        return;
    }
    for (auto child : root->childrens)
    {
        traverse(child, onPath);
    }
}
void dfs(vector<vector<pair<int, int>>> &graph, vector<bool> &visited, vector<int> &onPath, int u)
{
    if (visited[u])
    {
        return;
    }
    visited[u] = true;
    for (int i = 0; i < graph[u].size(); ++i)
    {
        int v = graph[u][i].first;
        dfs(graph, visited, onPath, v);
    }
}

/*最短路径，扩散类问题*/
void bfs(vector<vector<pair<int, int>>> &graph, int start)
{
    // 技巧：状态只有抽象成基本类型(最常见的string)才能加入unordered_set
    vector<bool> visited(graph.size(), false);
    queue<int> qu;
    qu.push(start);
    visited[start] = true;
    while (!qu.empty())
    {
        int u = qu.front();
        qu.pop();
        for (int i = 0; i < graph[u].size(); ++i)
        {
            int v = graph[u][i].first;
            if (!visited[v])
            {
                visited[v] = true;
                qu.push(v);
            }
        }
    }
}
typedef vector<vector<int>> Graph;
// 搜索类问题模板
//  从 s 开始 BFS 遍历图的所有节点，且记录遍历的步数
//  当走到目标节点 target 时，返回步数
int bfs(const Graph &graph, int x1, int y1, int x2, int y2)
{
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    vector<vector<bool>> visited(graph.size(), vector<bool>(graph[0].size(), false));
    queue<pair<int, int>> q;
    q.push({x1, y1});
    visited[x1][y1] = true;

    int step = 0;
    while (!q.empty())
    {
        int sz = q.size();
        for (int i = 0; i < sz; i++)
        {
            auto [u, v] = q.front();
            q.pop();
            // 判断是否到达终点
            if (u == x2 && v == y2)
            {
                return step;
            }
            // 扩散搜索遍历的是方向数组！！！
            for (auto [dx, dy] : dirs)
            {
                int nx = u + dx;
                int ny = v + dy;
                if (true) // 需要判断越界
                {
                    if (!visited[nx][ny])
                    {
                        q.push({nx, ny});
                        visited[nx][ny] = true;
                    }
                }
            }
        }
        step++;
    }
    // 如果走到这里，说明在图中没有找到目标节点
    return -1;
}

int main()
{
    /*一般建立图给的都是边,所以这里给定固定的两种最简单的建图方式*/

    // 1.邻接矩阵，需要更多的空间，好处：可快速判断两个节点的连接情况和某节点的入度出度
    int u, v, weight;
    vector<vector<int>> graph_1;
    graph_1[u][v] = weight;
    graph_1[v][u] = weight;

    // 2.邻接表，好处：省空间(其实就是紧缩型的矩阵,为了紧缩，我放弃了索引来存信息，使用值来存)
    vector<vector<int>> graph_;             // 如果不需要权重，这个就可以，形如：{{2,3},{3},{1}};
    vector<vector<pair<int, int>>> graph_2; // 形如：{{[2,10],[3,10]},{[3,10]},{[1,10]}} 注：实际的pair也是{}
    graph_2[u].push_back({v, weight});

    // 3.对于所有的以1开的，大胆偏移一格，要不改的地方太多,会造成你的慌乱
}