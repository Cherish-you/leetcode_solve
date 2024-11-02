#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX 10 // 以INT_MAX表示无穷

struct EdgeNode
{
    int weight; // 记录一下边的权值
    int adjvex; // 由于头节点已经包含了顶点到索引的映射，所以这里直接记录索引
    struct EdgeNode *next;
};

struct VexHeadNode
{
    char vex;
    struct EdgeNode *first;
};

struct Graph
{
    struct VexHeadNode *vev[MAX];
    int vexNum;
    int edgeNum;
};

// 这里这样写已经包含了顶点到索引的映射
void createGraph(int vexMatrix[MAX][MAX], int vex, int edge)
{
    for (int i = 0; i < MAX; ++i)
    {
        for (int j = 0; j < MAX; ++j)
        {
            if (vexMatrix[i][j] != 0 || vexMatrix[i][j] != INT_MAX)
            {
            }
        }
    }
}

vector<int> DFS(Graph &g, char v)
{
    int visited[MAX] = {0};
    vector<int> vlist;
    for (int i = 0; i < g.vexNum; i++)
    {
        if (g.vev[i]->vex == v)
        {
            visited[i] = 1;
            vlist.push_back(i);
            DFSTraverse(g, i, visited, vlist);
        }
    }
}

void DFSTraverse(Graph &g, int v, int visited[], vector<int> &vlist)
{
    EdgeNode *p = g.vev[v]->first;
    while (p != NULL)
    {
        int index = g.vev[v]->first->adjvex;
        if (visited[index] == 0)
        {
            vlist.push_back(index);
            visited[index] = 1;
            DFSTraverse(g, index, visited, vlist);
        }
        p = p->next;
    }
}

void bfs(vector<vector<int>> &graph, int x, int y)
{
    int hang = graph.size();
    int lie = graph[0].size();
    int visited[hang][lie] = {0};
    queue<pair<int, int>> q;
    q.push(make_pair(x, y)); // 扩展一个结点要进行的操作：入队，置为已访问，
    visited[x][y] = 1;

    while (!q.empty())
    {
        auto [a, b] = q.front();
        q.pop();
        for (int i = a - 1; i <= a + 1; ++i)
        {
            for (int j = b - 1; j <= b + 1; ++j)
            {
                if(visited[i][j]==0&&i<hang&&i>=0&&j<lie&&j>=0) {
                    q.push(make_pair(i,j));
                    visited[i][j]=1;
                }
            }
        }
    }
}

int main()
{
}