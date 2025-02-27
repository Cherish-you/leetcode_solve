#include <iostream>
#include <vector>

using namespace std;

/*动态规划：
一.先写递归式（要全面穷举所有的后继状态）
1.确定函数意义，问题中变化的量是关键
2.dp(状态1, 状态2):
    出口
    ...

    for 选择 in 所有可能的选择:
        # 此时的状态已经因为做了选择而改变
        result = 求最值(result, dp(状态1, 状态2))
    return result

3.出口：问题已经不能向下分解，是以当前函数的视角写的，单独罗列各种的再尝试完善：
if (i < 0) {//无可选元素
    return N == 0 ? 0 : -1e9; // 如果容量为0返回0，否则返回一个不可能的低值
}
if (N < 0) {//有可选元素但是超过容量限制
    return -1e9; // 返回一个不可能的低值,表示此路径无效
}
if(N==0)
    return 0;


二.改动态规划
函数变数组，状态变为数组维度，状态个数为数组个数，依据出口给数组设定计算起点
比如下面，根据递归式，应该有nums.size()+2个状态；根据出口return 0，计算入口就是dp[0]=dp[1]=0;
*/

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
        if (amount < 0)
        {
            return -1;
        }

        int ans = INT_MAX;
        for (int i = 0; i < coins.size(); ++i)
        {
            ans = 1 + min(ans, coinChange(coins, amount - coins[i]));
        }

        return ans;
    }
};

int main()
{
}