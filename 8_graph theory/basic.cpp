/*实际问题如何抽象成图：确定一个边集，一个点集就是一幅图，
不要刻意记图的基本结构，因为太多样，怎么适合怎么来*/
#include <vector>
#include <iostream>
#include <unordered_set>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

class Graph_matrix
{
    vector<int> vertices;       // 把具体的点映射到索引编号
    vector<vector<int>> adjMat; // 以索引编号建立矩阵

public:
    Graph_matrix(vector<int> &&vertices, vector<vector<int>> &&adjMat)
    {
        this->vertices = vertices;
        this->adjMat = adjMat;
    }

    void addVertices(int ver)
    {
        vertices.emplace_back(ver);
        // 二维矩阵的扩充：先扩充行，再扩充列
        int size = vertices.size();
        adjMat.emplace_back(vector<int>(size, 0));
        for (int i = 0; i < adjMat.size() - 1; ++i)
        {
            adjMat[i].emplace_back(0);
        }
    }
    void addEdge(int v1, int v2)
    {
        int index_1 = -1;
        int index_2 = -1;
        for (int i = 0; i < vertices.size(); ++i)
        {
            if (vertices[i] == v1)
            {
                index_1 = i;
            }
            if (vertices[i] == v2)
            {
                index_2 = i;
            }
            if (index_1 != -1 && index_2 != -1)
            {
                break;
            }
        }
        if (index_1 == -1 || index_2 == -1)
        {
            cout << "Error: vertex not found" << endl;
            return;
        }
        adjMat[index_1][index_2] = 1;
        adjMat[index_2][index_1] = 1;
    }

    void deleteVertices(int ver)
    {
        int index_1 = -1;
        for (int i = 0; i < vertices.size(); ++i)
        {
            if (vertices[i] == ver)
            {
                index_1 = ver;
            }
        }
        if (index_1 == -1)
        {
            cout << "Error: vertex not found" << endl;
            return;
        }
        vertices.erase(vertices.begin() + index_1);
        adjMat.erase(adjMat.begin() + index_1);
        for (int i = 0; i < adjMat.size(); ++i)
        {
            adjMat[i].erase(adjMat[i].begin() + index_1);
        }
    }

    void deleteEdge(int v1, int v2)
    {
        int index_1 = -1;
        int index_2 = -1;
        for (int i = 0; i < vertices.size(); ++i)
        {
            if (vertices[i] == v1)
            {
                index_1 = i;
            }
            if (vertices[i] == v2)
            {
                index_2 = i;
            }
            if (index_1 != -1 && index_2 != -1)
            {
                break;
            }
        }
        if (index_1 == -1 || index_2 == -1)
        {
            cout << "Error: vertex not found" << endl;
            return;
        }
        adjMat[index_1][index_2] = 0;
        adjMat[index_2][index_1] = 0;
    }
};

// 邻接表，用unordered_map<vertex*,vector<vertex*>>实现,这样直接关联了点和它的链表

// 遍历需要后继，所以后一种更适用
struct Node
{
    int val;
    std::vector<Node *> children;
};
class Graph
{
private:
    vector<Node *> point;

public:
    void traverse_map(const Graph &g)
    {
        unordered_set<Node *> visited;
        vector<Node *> path;
        for (int i = 0; i < point.size(); ++i)
        { // 非联通才这样，要不只执行一遍就行了
            traverse(g.point[i], visited, path);
        }
    }
    void traverse(Node *root, unordered_set<Node *> visited, vector<Node *> &path)
    {
        if (root == nullptr || visited.count(root))
            return;
        path.push_back(root);
        visited.emplace(root);
        for (int i = 0; i < root->children.size(); ++i)
        {
            traverse(root->children[i], visited, path);
        }
    }

    void level_map(Graph &g, Node *root, vector<Node *> &path)
    { // 以root开始的层序，求最短路径
        if (root == nullptr)
            return;
        queue<Node *> qu;
        qu.push(root);
        while (!qu.empty())
        {
            for (int i = 0; i < qu.size(); ++i)
            {
                Node *cur = qu.front();
                qu.pop();
                path.emplace_back(cur);
                for (int i = 0; i < cur->children.size(); ++i)
                {
                    if (cur->children[i] != nullptr)
                        qu.push(cur->children[i]);
                }
            }
        }
    }
};

// 解决的问题：有向无环图的确定务调度执行顺序：有向图判断有没有环，有前置课的课程安排
// 层序遍历，图适合用邻接矩阵形式，只不过起点为入度为0的节点，层序遍历完整个图来判断
vector<int> topological_sort(int num_nodes, const vector<pair<int, int>> &edges)
{
    // 构建入度表和邻接表
    vector<int> in_degree(num_nodes, 0);
    vector<vector<int>> adj_list(num_nodes);

    for (const auto &edge : edges)
    {
        int u = edge.first;
        int v = edge.second;
        adj_list[u].push_back(v);
        in_degree[v]++;
    }

    // 初始化队列，将所有入度为 0 的节点入队
    queue<int> q;
    for (int i = 0; i < num_nodes; ++i)
    {
        if (in_degree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> topo_order;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        topo_order.push_back(node);

        // 遍历当前节点的邻居，并将其入度减 1
        for (int neighbor : adj_list[node])
        {
            in_degree[neighbor]--;
            // 如果入度变为 0，则加入队列
            if (in_degree[neighbor] == 0)
            {
                q.push(neighbor);
            }
        }
    }

    // 如果拓扑排序包含的节点数不等于图中的节点数，说明存在环
    if (topo_order.size() != num_nodes)
    {
        return {}; // 表示有环
    }

    return topo_order;
}

// 判断一个图是二分图，使用两种颜色染色
bool isBipartite(int n, vector<vector<int>> &graph)
{
    vector<int> color(n, -1); //-1表示未染色，0表示一种颜色，1表示另一种颜色
    for (int i = 0; i < n; ++i)
    {
        if (color[i] == -1)
        {
            queue<int> q;
            q.push(i);
            color[i] = 0;

            while (!q.empty())
            {
                int u = q.front();
                q.pop();

                for (int v : graph[u])
                {
                    if (color[v] == -1)
                    {
                        color[v] = 1 - color[u];
                        q.push(v);
                    }
                    else if (color[v] == color[u])
                    {
                        return false; // 存在同色相邻节点
                    }
                }
            }
        }
    }

    return true;
}
// 最大匹配：两个点集合，每个点集合里的点最多与一条边相连，使得匹配的边数尽可能多
//  二分图解决的问题:最大匹配，男和女、任务和员工找最大的匹配数;
#include <string.h>
#define MAXN 1000 // 节点数
// vector<int> graph[MAXN];  // 二分图
int matchL[MAXN] = {-1};
int matchR[MAXN] = {-1};
bool visited[MAXN] = {0};
// DFS搜索增广路径,不重要，知道这个代码就行
bool dfs(int u, vector<vector<int>> &graph)
{
    for (int v : graph[u])
    {
        if (!visited[v])
        {
            visited[v] = true;
            // 如果右侧节点v没有匹配，或者右侧节点v的匹配节点可以找到增广路径
            if (matchR[v] == -1 || dfs(matchR[v], graph))
            {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}
int getMaxMatch(vector<vector<int>> &graph)
{
    int maxMatching = 0;
    int n = graph.size();
    // 尝试为每个左侧节点u寻找增广路径
    for (int u = 0; u < n; u++)
    {
        memset(visited, 0, sizeof(visited)); // 重置访问标记
        if (dfs(u, graph))
        {
            maxMatching++;
        }
    }
    return maxMatching;
}

// 并查集：
class UnionFind
{
public:
    vector<int> parent; // 存储所有节点的父节点
    vector<int> rank;   // 存储所有节点的秩，即树高
    int numSet;         // 节点个数
    UnionFind(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        numSet = n;
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    } // 默认所有节点独立，即每个节点的父节点都是自己

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    } // 查找当前节点的根父节点同时把路径上节点的父节点都设置为这个根父节点

    void unite(int x, int y)
    {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx == rooty)
            return;
        if (rank[rootx] < rank[rooty])
        {
            parent[rootx] = rooty;
        }
        else if (rank[rootx] > rank[rooty])
        {
            parent[rooty] = rootx;
        }
        else
        {
            parent[rooty] = rootx;
            rank[rootx]++; // 因为前两种是明确不会造成秩改变的
        }
        numSet--;
    }
};
// 最小生成树： 加边法
struct Edge
{
    int u, v, weight;
    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};
// edges为图的边集，num_nodes为节点个数
vector<Edge> kruskal(int num_nodes, vector<Edge> &edges)
{
    vector<Edge> mst; // 存最少的边连接所有点
    sort(edges.begin(), edges.end());
    UnionFind ds(num_nodes);

    for (const Edge &edge : edges)
    {
        if (ds.find(edge.u) != ds.find(edge.v))
        {
            mst.push_back(edge);
            ds.unite(edge.u, edge.v);
        }
    }
    return mst;
}

// 有向或无向，带权权非负图：单源最短路径 dijkstra
#include <climits>
#include <algorithm>
void dijkstra(int src, const vector<vector<int>> &graph, vector<int> &dist, vector<int> &prev)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    dist.assign(n, INT_MAX); // 记录最短距离
    prev.assign(n, -1);      // 记录该点的前驱点
    dist[src] = 0;

    for (int i = 0; i < n; ++i)
    {
        int u = -1;
        int min_dist = INT_MAX;
        // 找到当前未访问节点中距离最小的节点
        for (int j = 0; j < n; ++j)
        {
            if (!visited[j] && dist[j] < min_dist)
            {
                u = j;
                min_dist = dist[j];
            }
        }

        if (u == -1)
            break; // 所有可达节点均已访问
        visited[u] = true;

        // 更新邻居节点的距离
        for (int v = 0; v < n; ++v)
        {
            if (graph[u][v] != INT_MAX && !visited[v] && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }
}
// 根据前驱点数组来打印路径
void print_path(int src, int dest, const vector<int> &prev)
{
    if (dest == -1)
    {
        cout << "没有路径" << endl;
        return;
    }
    vector<int> path;
    for (int at = dest; at != -1; at = prev[at])
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    if (path[0] == src)
    {
        for (int i = 0; i < path.size(); ++i)
        {
            if (i > 0)
                cout << " -> ";
            cout << path[i];
        }
        cout << endl;
    }
    else
    {
        cout << "没有路径" << endl;
    }
}

// 有向或无向，权可为负但不能是负权环的图中每个点到其他点的最短路径（使用邻接矩阵）
void floyd_warshall(vector<vector<int>> &dist, vector<vector<int>> &next)
{
    int n = dist.size();
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}
