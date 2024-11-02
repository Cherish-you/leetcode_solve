#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// 这种是在有限数量下选择

typedef pair<int, int> Coins;
#define val first
#define count second

int backtrack(vector<Coins> &coins, int amount, int i, vector<vector<int>> &cache)
{
    if (i < 0)
    {
        if (amount == 0)
        {
            return 0;
        }
        return INT_MAX / 2;
    } // i<0时，说明已经没有硬币可选了，如果amount为0，说明已经凑齐了，返回0，否则返回一个很大的值，表示凑不齐
    if (cache[i + 1][amount] != -1)
    {
        return cache[i + 1][amount];
    } //! cache是和退出条件具有同等地位的，优先判断，满足直接返回不进入函数内部

    if (coins[i].val > amount || coins[i].count <= 0)
    { // 受限制一定不能选：
        cache[i][amount] = backtrack(coins, amount, i - 1, cache);
        return cache[i][amount];
    } //! 只记录本函数的返回值
    int noChoice = backtrack(coins, amount, i - 1, cache);
    coins[i].count--;
    int choice = backtrack(coins, amount - coins[i].val, i, cache) + 1;
    coins[i].count++;
    cache[i + 1][amount] = min(noChoice, choice);
    return cache[i + 1][amount]; //! 只记录本函数的返回值
}

int coins(vector<Coins> &coins, int amount)
{
    int n = coins.size() - 1;
    vector<vector<int>> cache(n + 2, vector<int>(amount + 1, -1)); // i一致前移一格来记录，所以有size+1个
    int res = backtrack(coins, amount, n, cache);
    return res < INT_MAX / 2 ? res : -1;
}

int main()
{
    vector<Coins> c = {{1, 4}, {2, 2}, {5, 1}};
    int amount = 11;
    cout << coins(c, amount) << endl;
    return 0;
}