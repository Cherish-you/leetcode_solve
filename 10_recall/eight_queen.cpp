#include <iostream>
#include <vector>

using namespace std;

void backtrack(vector<vector<int>> &ans, vector<int> &path, int hang, int lieSize, vector<bool> &lie, vector<bool> &dia1, vector<bool> &dia2)
{
    // hang表示放置的皇后数量,由于每行有且只有一个皇后，所以结果记录列就好了
    // 这样天然的约束了行，后面剪枝需要约束列，两个斜对角,同一个对角线的行和列的差值相同，以这个差值为索引标识位
    if (hang == lieSize)
    {
        ans.push_back(path);
        return;
    }

    for (int i = 0; i < lieSize; ++i)
    {
        int zhu = hang + i;
        int fu = hang - i + lieSize - 1;
        if (!lie[i] && !dia1[zhu] && !dia2[fu])
        {
            path.push_back(i);
            lie[i] = true;
            dia1[zhu] = true;
            dia2[fu] = true;

            backtrack(ans, path, hang + 1, lieSize, lie, dia1, dia2);

            path.pop_back();
            lie[i] = false;
            dia1[zhu] = false;
            dia2[fu] = false;
        }
    }
}

void eight_queen(int n, vector<vector<int>> &ans)
{
    vector<int> path; // 空容器
    int hang = 0;
    int lieSize = n;
    vector<bool> lie(lieSize, false);
    vector<bool> dia1(2 * n - 1, false);
    vector<bool> dia2(2 * n - 1, false);

    backtrack(ans, path, hang, lieSize, lie, dia1, dia2);
}

int main()
{

    int n = 8;
    vector<vector<int>> ans;
    eight_queen(n, ans);
    int count = 0;
    for (int i = 0; i < ans.size(); ++i)
    {
        for (int j = 0; j < ans[i].size(); ++j)
        {
            cout << ans[i][j] << " ";
        }
        cout << "第" << ++count << "种";
        cout << endl;
    }
}
