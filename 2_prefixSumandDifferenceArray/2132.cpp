#include <vector>
#include <iostream>

using namespace std;

/*
给你一个 m x n 的二进制矩阵 grid ，每个格子要么为 0 （空）要么为 1 （被占据）。

给你邮票的尺寸为 stampHeight x stampWidth 。我们想将邮票贴进二进制矩阵中，且满足以下 限制 和 要求 ：

覆盖所有 空 格子。
不覆盖任何 被占据 的格子。
我们可以放入任意数目的邮票。
邮票可以相互有 重叠 部分。
邮票不允许 旋转 。
邮票必须完全在矩阵 内 。
如果在满足上述要求的前提下，可以放入邮票，请返回 true ，否则返回 false*/

/*思路：
找到可以放的位置(放不放的下另说)：利用前缀和找区域和为0的区域；
(邮票可重叠，故尽可能多的放),在上面找到的区域去放，实质就是用差分来做到区域同加1的操作，
然后遍历grid，如果grid[i][j]==0&&diff[i][j]==0，就是false*/

vector<vector<int>> getPrefix(const vector<vector<int>> &grid)
{
    int m = grid.size() + 1;
    int n = grid[0].size() + 1;
    vector<vector<int>> prefix(m, vector<int>(n, 0));
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + grid[i - 1][j - 1];
        }
    }
    return prefix;
}
int getNum(const vector<vector<int>> &prefix, int x1, int y1, int x2, int y2)
{
    return prefix[x2 + 1][y2 + 1] - prefix[x1][y2 + 1] - prefix[x2 + 1][y1] + prefix[x1][y1];
}

void update(vector<vector<int>> &diff, int x_1, int y_1, int x_2, int y_2, int val)
{
    diff[x_1][y_1] += val;
    int row = diff.size();
    int col = diff[0].size();
    if (x_2 + 1 < row)
        diff[x_2 + 1][y_1] -= val;
    if (y_2 + 1 < col)
        diff[x_1][y_2 + 1] -= val;
    if ((x_2 + 1 < row) && (y_2 + 1 < col))
        diff[x_2 + 1][y_2 + 1] += val;
}

bool isPossibleToStamp(vector<vector<int>> &grid, int stampHeight, int stampWidth)
{
    vector<vector<int>> pre = getPrefix(grid);

    int row = grid.size();
    int col = grid[0].size();
    if (getNum(pre, 0, 0, row - 1, col - 1) == row * col)
    {
        return true;
    }

    // 反正有办法识别，不如先忽略原矩阵的差别，去搞计数矩阵的差分数组，所以直接就是0，不用再求
    vector<vector<int>> diff(row, vector<int>(col, 0));

    for (int i_2 = stampHeight - 1; i_2 < row; i_2++)
    {
        for (int j_2 = stampWidth - 1; j_2 < col; j_2++)
        {
            int i_1 = i_2 - stampHeight + 1;
            int j_1 = j_2 - stampWidth + 1;
            if (getNum(pre, i_1, j_1, i_2, j_2) == 0)
            {
                update(diff, i_1, j_1, i_2, j_2, 1);
            }
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j] == 0 && diff[i][j] == 0) // 计数为0并且为空格子才说明false
                return false;
        }
    }
    return true;
}

int main()
{
    vector<vector<int>> grid = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    int stampHeight = 2;
    int stampWidth = 2;
    cout << isPossibleToStamp(grid, stampHeight, stampWidth) << endl;
    return 0;
}