#include <vector>
#include <iostream>

using namespace std;

class Solution
{
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        vector<vector<int>> prefix = getPrefixArray(mat);
        int row = mat.size();
        int col = mat[0].size();
        vector<vector<int>> answer(row, vector<int>(col, 0));
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                answer[i][j] = getMatrixSum(prefix, i - k, j - k, i + k, j + k);
            }
        }
        return answer;
    }
    vector<vector<int>> getPrefixArray(const vector<vector<int>> &arr) //// 因为是以指针传的数组，所以同时给上行，列参数，
    {

        int row = arr.size() + 1;
        int column = arr[0].size() + 1;
        vector<vector<int>> prefix(row, vector<int>(column, 0));

        for (int i = 1; i < row; ++i)
        {
            for (int j = 1; j < column; ++j)
            {
                prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + arr[i - 1][j - 1];
            }
        }
        return prefix;
    }
    int getMatrixSum(const vector<vector<int>> &prefix, int x_1, int y_1, int x_2, int y_2)
    {
        if (x_1 < 0) // 因为可能越界，所以添加一波修正
        {
            x_1 = 0;
        }
        if (y_1 < 0)
        {
            y_1 = 0;
        }
        if (x_2 >= prefix.size() - 1)
        {
            x_2 = prefix.size() - 2;
        }
        if (y_2 >= prefix[0].size() - 1)
        {
            y_2 = prefix[0].size() - 2;
        }
        int res = prefix[x_2 + 1][y_2 + 1] - prefix[x_1][y_2 + 1] - prefix[x_2 + 1][y_1] + prefix[x_1][y_1];
        return res;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> arr = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int k = 1;
    vector<vector<int>> ans = s.matrixBlockSum(arr, k);
    for (int i = 0; i < ans.size(); ++i)
    {
        for (int j = 0; j < ans[0].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}