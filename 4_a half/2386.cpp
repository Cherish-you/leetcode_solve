#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

long long getSum(vector<int> &nums, int k)
{
    long long sum = 0;
    int size = nums.size();
    for (int i = 0; i < size; i++)
    { // 求数组最大和
        if (nums[i] >= 0)
        {
            sum = sum + nums[i];
        }
        else
        {
            nums[i] = -nums[i];
        }
    }
    ranges::sort(nums);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.emplace(0, 0);
    while (--k)//找第k个小的子序列
    {
        auto [s, i] = pq.top();
        pq.pop();

        if (i < size) // 添加的前提，未满
        {
            pq.emplace(s + nums[i], i + 1); // 添加一个元素
            if (i)                          // 队列是有序的，添加和替换是并行的，因为不能确定是添加更小还是替换更小
            {
                pq.emplace(s + nums[i] - nums[i - 1], i + 1); // 替换一个元素
            }
        }
    }
    return sum - pq.top().first;
}

// 78 求所有子集
// dfs
void dfs(vector<vector<int>> &ans, vector<int> &nums, vector<int> &path, int index)
{
    if (index == nums.size())
    {
        ans.push_back(path);
        return;
    }

    dfs(ans, nums, path, index + 1); // i不选，进入下一个

    path.push_back(nums[index]);
    dfs(ans, nums, path, index + 1);
    path.pop_back();
}
vector<vector<int>> subsets(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
    {
        return {{}};
    }

    vector<vector<int>> ans;
    vector<int> path;

    dfs(ans,nums,path,0);
    return ans;
}

int main()
{

    return 0;
}