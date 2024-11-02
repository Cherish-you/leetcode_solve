#include <iostream>
#include <vector>

using namespace std;

// 凑零钱，可无限重复取一个，完全背包类型


int backtrack(vector<int> &coins, int i, int amount)
{
    if (i < 0)
    {
        if (amount == 0)
        {
            return 0;
        }
        return INT_MAX / 2;
    }
    if (coins[i] > amount)
    {
        return backtrack(coins, i - 1, amount);
    }
    return min(backtrack(coins, i - 1, amount), backtrack(coins, i, amount - coins[i]) + 1);
}
int coinChange(vector<int> &coins, int amount)
{
    int n = coins.size();
    int ans = backtrack(coins, n - 1, amount);
    return ans == INT_MAX / 2 ? -1 : ans;
}

int _dp(vector<int> &coins, int amount)
{
    int size = coins.size();

    vector<vector<int>> dp(size + 1, vector<int>(amount + 1, INT_MAX / 2));
    dp[0][0] = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j <= amount; ++j)
        {
            if (coins[i] > j)
            {
                dp[i + 1][j] = dp[i][j];
            }
            else
            {
                dp[i + 1][j] = min(dp[i][j], dp[i + 1][j - coins[i]] + 1);
            }
        }
    }
    int res = dp[size][amount];
    return res < INT_MAX / 2 ? res : -1;
}

int main()
{
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    cout << coinChange(coins, amount) << endl;
    // cout << _dp(coins, amount) << endl;

    return 0;
}