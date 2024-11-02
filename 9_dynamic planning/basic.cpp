#include <iostream>
#include <vector>

using namespace std;
//*解决选择与不选择的决策问题，这个的子问题和函数定义都是类似的

// 题目：给定一个数组，求最大子序列和，且子序列中不能相邻

// 递归  函数定义：前i个数的最大子序列和=前i-1个数的最大子序列和 或 前i-2个数的最大子序列和+第i个数
int dfs(vector<int> &nums, int i) // 指数级时间复杂度
{
    if (i < 0)
    {
        return 0;
    }
    int ans = max(dfs(nums, i - 1), dfs(nums, i - 2) + nums[i]);
    return ans;
}

// 记忆化搜索 时间o(n) 空间o(n)
int dfs_(vector<int> &nums, int i, vector<int> &cache)
{
    if (i < 0)
    {
        return 0;
    }
    if (cache[i] != -1)
    {
        return cache[i];
    }
    int ans = max(dfs_(nums, i - 1, cache), dfs_(nums, i - 2, cache) + nums[i]);
    cache[i] = ans;
    return ans;
}

// 非递归写法， 从下往上，只有归 动态规划，时间o(n),空间复杂度为o（n）
int dfs_2(vector<int> &nums, int i)
{
    int n = nums.size();
    vector<int> answer(n + 2, 0);
    answer[0] = answer[1] = 0;
    for (int j = 0; j < n; j++)
    {
        answer[j + 2] = max(answer[j + 1], answer[j] + nums[j]);
    }
    return answer[n + 1];
}

// 记录两个值就可以算答案,且这两个值可同时出现 时间o(n),空间o(1)
int dfs_3(vector<int> &nums, int i)
{
    int n = nums.size();
    int f0 = 0;
    int f1 = 0;
    for (int j = 0; j < n; j++)
    {
        int new_f = max(f0, f1 + nums[j]);
        f0 = f1;
        f1 = new_f;
    }
    return f1;
}

// 322 零钱兑换 定义函数:达到amount的最小硬币数coinChange(coins,amount)=
class CoinChange
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        if (amount == 0)
        {
            return 0;
        }
        if(amount < 0)
        {
            return -1;
        }

        int ans = INT_MAX;
        for(int i=0;i<coins.size();++i)
        {
            ans=1+min(ans,coinChange(coins,amount-coins[i]));
        }
        
        return ans;

    }
};

int main()
{
}