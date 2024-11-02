#include <iostream>
#include <vector>
#include <set>
using namespace std;

// 这里涉及到一种剪枝的方法 34，43一样，排序+从start开始做选择

void backtrack(vector<int> &nums, int target, multiset<multiset<int>> &ans, multiset<int> &path, int i, int start)
{
    if (i == nums.size() || target <= 0)
    {
        if (target == 0)
        {
            if (ans.find(path) == ans.end())
            {
                ans.emplace(path);
            }
            return;
        }
        return;
    }

    for (int j = start; j < nums.size(); j++)
    {
        path.emplace(nums[j]);
        backtrack(nums, target - nums[j], ans, path, i + 1, j);
        path.erase(path.find(nums[j]));
    }
}

void subset_sum(vector<int> &nums, int target, multiset<multiset<int>> &ans)
{
    multiset<int> path;
    int start = 0; // 开始的索引
    backtrack(nums, target, ans, path, 0, start);
}
/*
上面方法的效率太低了，应该过程中剪枝而不是对于结果筛选*/

int main()
{
    vector<int> nums = {3, 4, 5};
    int target = 9;
    multiset<multiset<int>> ans;
    subset_sum(nums, target, ans);

    for (auto it = ans.begin(); it != ans.end(); it++)
    {
        for (auto it2 = it->begin(); it2 != it->end(); it2++)
        {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    return 0;
}