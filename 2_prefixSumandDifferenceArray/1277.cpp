#include <iostream>
#include <vector>

using namespace std;

/*给你一个 m * n 的矩阵，矩阵中的元素不是 0 就是 1，请你统计并返回其中完全由 1 组成的 正方形 子矩阵的个数。*/

vector<vector<int>> getPrefix(const vector<vector<int>> &matrix)
{
    int row = matrix.size() + 1;
    int col = matrix[0].size() + 1;
    vector<vector<int>> prefix(row, vector<int>(col, 0));

    for (int i = 1; i < row; ++i)
    {
        for (int j = 1; j < col; ++j)
        {
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + matrix[i - 1][j - 1];
        }
    }
    return prefix;
}

int getMatrixNum(const vector<vector<int>> &prefix, int x_1, int y_1, int x_2, int y_2)
{
    // 用固定（0，0）点，做矩形理解
    int res = prefix[x_2 + 1][y_2 + 1] - prefix[x_1][y_2 + 1] - prefix[x_2 + 1][y_1] + prefix[x_1][y_1];
    return res;
}
bool checkIs(const vector<vector<int>> &pre, int i, int j, int length)
{ // 判断这个正方形是否满足要求，需要边长，左上角坐标，前缀和数组

    int x_2 = i + length - 1; // 右下角坐标，1<=length<=矩阵小边边长
    int y_2 = j + length - 1; // 理论上没有越界的可能

    int res = getMatrixNum(pre, i, j, x_2, y_2);
    if (res == length * length)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int getNumOfMatrix(const vector<vector<int>> &matrix)
{
    vector<vector<int>> prefix = getPrefix(matrix); // 获取前缀和数组

    int hang = matrix.size();
    int lie = matrix[0].size();
    int ans = 0;
    for (int i = 0; i < hang; ++i)
    {
        for (int j = 0; j < lie; ++j)
        { // 遍历原始矩阵的每个点
            int left = 1;
            int right = min(hang - i, lie - j); // 查找最大边长
            int res = 0;

            while (left <= right)
            {
                int squLength = (right - left) / 2 + left;
                if (checkIs(prefix, i, j, squLength))
                {
                    // res = max(res, squLength);//这样写也可以获得结果或者最后left-1为满足条件的最大值
                    left = squLength + 1;
                }
                else
                {
                    right = squLength - 1;
                }
            }
            res = left - 1;
            ans += res;
        }
    }
    return ans;
}

int main()
{
    vector<vector<int>> matrix = {{0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}};
    // vector<vector<int>> matrix_2 = {{1, 0, 1}, {1, 1, 0}, {1, 1, 0}};
    cout << getNumOfMatrix(matrix) << endl;
}