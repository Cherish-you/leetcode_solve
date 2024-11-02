#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dijkstra(vector<vector<int>> &graph, int n, int k) // 从k出发
{
    vector<int> dis(n, INT_MAX / 2);
    vector<int> done(n, 0);

    dis[k - 1] = 0;
    while (true)
    {
        int x = -1;
        for (int i = 0; i < n; i++)
        {
            if (!done[i] && (x < 0 || dis[i] < dis[x]))
            {
                x = i;
            }
        }
        if (x < 0)
        {
            return ranges::max(dis);
        }
        if (dis[x] == INT_MAX / 2)
        {
            return -1;
        }
        done[x] = true;
        for (int y = 0; y < n; y++)
        {
            dis[y] = min(dis[y], dis[x] + graph[x][y]);
        }
    }
}

int main()
{

    return 0;
}