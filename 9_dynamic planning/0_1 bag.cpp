#include <iostream>
#include <vector>

using namespace std;

// 0-1 背包问题

// 494 类型：可转化为恰好装capacity

int dfs(int i, int capacity, vector<int> &nums)
{
    if (i < 0)
    {
        if (capacity == 0)
        {
            return 1;
        }
        return 0;
    }
    if (nums[i] > capacity)
    {
        return dfs(i - 1, capacity, nums);
    }

    return dfs(i - 1, capacity - nums[i], nums) + dfs(i - 1, capacity, nums);
}

int dfs_dp(int capacity, vector<int> &nums)
{
    int size = nums.size();
    vector<vector<int>> dp(size + 1, vector<int>(capacity + 1));
    dp[0][0] = 1; // 为了避免负数索引，将整个数组向后移了一格
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j <= capacity; ++j)
        {
            if (nums[i] > j)
            {
                dp[i + 1][j] = dp[i][j];
            }
            else
            {
                dp[i + 1][j] = dp[i][j] + dp[i][j - nums[i]];
            }
        }
    }
    return dp[size][capacity];
}

int findTargetSum(vector<int> &nums, int target)
{
    // p为正数的和，s为所有元素绝对值的和  s-p为负数绝对值的和
    // 所求为p-(s-p)=t p=(t+s)/2  于是问题变成了求和为p的子集个数

    int size = nums.size();
    int sum = 0;
    for (int i = 0; i < size; ++i)
    {
        sum = sum + nums[i];
    }
    target = target + sum;

    if (target < 0 || target % 2 == 1)
    {
        return 0;
    }
    target = target / 2;

    // return dfs(size - 1, target, nums);
    return dfs_dp(target, nums);
}

int main()
{
    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;
    cout << findTargetSum(nums, target);
}