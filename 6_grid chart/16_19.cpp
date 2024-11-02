#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// dfs 深度优先遍历网状图 大致模板是通用的
int dfs(vector<vector<int>> &graph, int x, int y)
{
    if (x < 0 || x >= graph.size() || y < 0 || y >= graph[0].size() || graph[x][y] == 1)
    { // 走格越界或已访问直接退出
        return 0;
    }

    graph[x][y] = 1; // 找到了，置返回值为1，标记已访问
    int cnt0 = 1;

    // x,y周围8个方向中0的个数
    for (int i = x - 1; i <= x + 1; ++i)
    {
        for (int j = y - 1; j <= y + 1; ++j)
        {
            cnt0 += dfs(graph, i, j);
        }
    }
    return cnt0;

    
}

queue<pair<int, int>> qu;
int bfs(vector<vector<int>> &grid, int x, int y)
{

    qu.push(make_pair(x, y));
    int cnt0 = 0;

    while (!qu.empty())
    {
        auto [x, y] = qu.front();
        qu.pop();
        grid[x][y] = 1;
        cnt0++;
        for (int i = x - 1; i <= x + 1; ++i)
        {
            for (int j = y - 1; j <= y + 1; ++j)
            {

                if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] != 0)
                {
                    continue;
                }
                qu.push(make_pair(i,j));//入队的都是grid[x][y]=0的点
            }
        }
    }
}

vector<int> pondSize(vector<vector<int>> &grid)
{
    vector<int> result;

    int hangSize = grid.size();
    int lieSize = grid[0].size();
    for (int i = 0; i < hangSize; ++i)
    {
        for (int j = 0; j < lieSize; ++i)
        {
            if (grid[i][j] == 0)
            {
                result.push_back(dfs(grid, i, j));
            }
        }
    }
    return result;
}

int main()
{
}