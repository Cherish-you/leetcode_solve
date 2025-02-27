#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*
1.全排列问题借助一个数组来记录每个元素是否被选择，剪掉重复选择同一元素的搜索分支，确保每个元素只被选择一次。
2.如果存在重复元素，我们需要在for前面约束相等元素在每轮中只能被选择一次，这通常借助一个unordered_set来实现。
3.子集和问题：集合不区分元素顺序，而搜索过程会输出所有顺序的结果，产生重复子集。我们在回溯前将数据进行排序，并设置一个变量来指示每一轮的遍历起始点，从而将生成重复子集的搜索分支进行剪枝。
4.对于子集和问题，数组中的相等元素会产生重复集合。我们利用数组已排序的前置条件，通过判断相邻元素是否相等实现剪枝，从而确保相等元素在每轮中只能被选中一次。
皇后问题旨在寻找将n个皇后放置到n*n尺寸棋盘上的方案，该问题的约束条件有行约束、列约束、主对角线和次对角线约束。为满足行约束，我们采用按行放置的策略，保证每一行放置一个皇后。
对于列约束用一个数组来记录每一列是否有皇后。对于对角线约束借助两个数组来分别记录该主、次对角线上是否存在皇后；难点在于找处在到同一主（副）对角线上格子满足的行列索引规律。
*/

// 这里涉及到两种剪枝

/*
不可重复的全排列
*/
void full_permutation(vector<int> &vec, vector<vector<int>> &ans, vector<int> &visited, vector<int> &path, int i)
{
    // i表示选择了几个元素
    if (i == vec.size())
    {
        ans.push_back(path);
        return;
    }

    for (int j = 0; j < vec.size(); j++)
    {
        if (!visited[j])
        {
            visited[j] = 1;
            path.push_back(vec[j]);
            full_permutation(vec, ans, visited, path, i + 1);
            visited[j] = 0;
            path.pop_back();
        }
    }
}

void permutation(vector<int> &vec, vector<vector<int>> &ans)
{
    vector<int> path;
    vector<int> visited(vec.size(), 0);
    // 标识索引是否被访问，如果标识值，就是非连续的不知多少个元素
    full_permutation(vec, ans, visited, path, 0);
}

/*
可重复的全排列,所用数组不需有序
*/
void dup_permutation(vector<int> &vec, vector<int> &path, vector<vector<int>> &ans, vector<int> &visited, int i)
{
    if (i == vec.size())
    {
        ans.push_back(path);
        return;
    }
    unordered_set<int> se; // 记录同层选择过的元素,不用回溯
    for (int j = 0; j < vec.size(); j++)
    {
        if (!visited[j] && se.find(vec[j]) == se.end())
        {
            se.insert(vec[j]);
            visited[j] = 1; // 再次回到该层转另一个选择时，这些操作是无效的
            path.push_back(vec[j]);
            dup_permutation(vec, path, ans, visited, i + 1);
            visited[j] = 0;
            path.pop_back();
        }
    }
}

void dupPermutation(vector<int> &vec, vector<vector<int>> &ans)
{
    vector<int> path;
    vector<int> visited(vec.size(), 0);
    dup_permutation(vec, path, ans, visited, 0);
}

int main()
{
    vector<int> vec = {1, 1, 4, 3};
    vector<vector<int>> ans;
    dupPermutation(vec, ans);

    int num = 0;
    for (int i = 0; i < ans.size(); ++i)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << "第" << ++num << "种" << endl;
        cout << endl;
    }
    cout << endl;
}