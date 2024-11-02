#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define RED 0
#define BLUE 1

// 1129
vector<int> bfs(vector<vector<int>> &red, vector<vector<int>> &blue, int n)
{
    vector<vector<vector<int>>> graph(2, vector<vector<int>>(n));
    for (int i = 0; i < red.size(); ++i)
    {
        graph[RED][red[i][0]].push_back(red[i][1]); // 红边
    }
    for (int j = 0; j < blue.size(); ++j)
    {
        graph[BLUE][blue[j][0]].push_back(blue[j][1]); // 蓝边
    }

    queue<pair<int, int>> qu;
    qu.push({RED, 0});
    qu.push({BLUE, 0});
    // 这里把一个结点拆成两个，因为有红蓝交替的要求， 队中取红的，就拓展它的蓝后继

    vector<vector<int>> answer(2, vector<int>(n, INT_MAX));
    answer[RED][0] = 0;
    answer[BLUE][0] = 0;
    while (!qu.empty())
    {
        auto [uColor, u] = qu.front(); // u和u的颜色
        qu.pop();

        int vColor = 1 - uColor; // 0(red)，1(blue)的互相切换

        for (int v : graph[vColor][u])
        { // 找u的后继
            if (answer[vColor][v] != INT_MAX)
            {
                continue;
            }
            answer[vColor][v] = answer[uColor][u] + 1;
            qu.push({vColor, v});
        }
    }

    vector<int> res(n);
    for (int i = 0; i < n; ++i)
    {
        res[i] = min(answer[RED][i], answer[BLUE][i]);
        if (res[i] == INT_MAX)
        {
            res[i] = -1;
        }
    }
    return res;
}

void update(vector<vector<int>> &red, vector<vector<int>> &blue, int n)
{
    vector<vector<vector<int>>> graph(2, vector<vector<int>>(n));
    for (int i = 0; i < red.size(); i++)
    {
        graph[0][red[i][0]].push_back(red[i][1]);
    }
    for (int j = 0; j < blue.size(); j++)
    {
        graph[1][blue[j][0]].push_back(blue[j][1]);
    }

    for (int i = 0; i < graph.size(); ++i)
    {
        for (int j = 0; j < graph[i].size(); ++j)
        {
            for (int k = 0; j < graph[i][j].size(); ++k)
            {
            }
        }
    }
}

// 1298
// todo 现在缺一个处理不能打开的逻辑，目前是完全跳过了不能打开的盒子，但是后续有可能拿到钥匙，可这个盒子的信息丢失了
//! 队列和栈的思想是无法兼容的，双端队列要么用作栈（只用一端或用两端制造单调序列），要么用作队列
int getMaxCandies(vector<int> &status, vector<int> candies, vector<vector<int>> &keys, vector<vector<int>> &containBoxes, vector<int> initBoxes)
{
    // initBoxes[i]表示盒子的编号      status[i]表示盒子i是否打开  candies[i]表示盒子i的糖果数量
    // keys[i][j]表示盒子i中可获得的钥匙编号  containBoxes[i][j]表示盒子i里的其他盒子编号

    int boxSize = status.size();     // 盒子数量
    vector<int> visited(boxSize, 0); // 记录盒子是否被访问过

    int maxNum = 0; // 开的盒子越多，肯定是越大
    queue<int> qu;  // 进这个队列的只能是可开的盒子

    for (int i = 0; i < initBoxes.size(); ++i)
    {
        if (status[initBoxes[i]] == 1) // 盒子是开的,需要以下操作
        {
            maxNum = maxNum + candies[initBoxes[i]];
            qu.push(initBoxes[i]);
            visited[initBoxes[i]] = 1;
            for (int j = 0; j < keys[initBoxes[i]].size(); ++j)
            {
                status[keys[initBoxes[i]][j]] = 1;
            }
        }
        else
        {
        }
    }

    while (!qu.empty())
    {
        int box = qu.front();
        qu.pop();

        for (int j = 0; j < containBoxes[box].size(); ++j) // 遍历可添加的盒子
        {
            if (visited[containBoxes[box][j]] == 0)
            {
                if (status[containBoxes[box][j]] == 1)
                {
                    maxNum = maxNum + candies[containBoxes[box][j]];
                    qu.push(containBoxes[box][j]);
                    visited[containBoxes[box][j]] = 1;
                    for (int k = 0; k < keys[containBoxes[box][j]].size(); ++k)
                    {
                        status[keys[containBoxes[box][j]][k]] = 1;
                    }
                }
            }
        }
    }

    return maxNum;
}

int main()
{
    vector<int> status = {1, 0, 1, 0};
    vector<int> candies = {7, 5, 4, 100};
    vector<vector<int>> keys = {{}, {}, {1}, {}};
    vector<vector<int>> containBoxes = {{1, 2}, {3}, {}, {}};
    vector<int> initBoxes = {0};

    cout << getMaxCandies(status, candies, keys, containBoxes, initBoxes);
    return 0;
}