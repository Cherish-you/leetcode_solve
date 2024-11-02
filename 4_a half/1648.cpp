#include <iostream>
#include <vector>

using namespace std;

#define mod 1000000007

class Solution
{
public:
    int maxProfit(vector<int> &vec, int orders)
    {
        int left = 0;
        int right = 1e9 - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (check(vec, mid, orders))
            {
                left = mid + 1;
            }
            else
                right = mid - 1;
        }
        int x = right + 1; // 最后一次卖出的价格
        long ans = 0;
        int size = vec.size();
        int cishu = orders;
        for (int j = 0; j < size; j++)
        {
            if (vec[j] > x)
            {
                cishu = cishu - (vec[j] - x);
                ans = ans + (long)(vec[j] + x + 1) * (long)(vec[j] - x) / 2;
                ans = ans % mod;
            }
        }
        if (cishu > 0)
        {
            ans = ans + (long)(cishu) * (long)(x);
            ans = ans % mod;
        }
        return ans;
    }

private:
    bool check(vector<int> &vec, int mid, int orders)
    {
        int sum = 0;
        for (int i : vec)
        {
            sum = sum + max(i - mid, 0); // 计算大于x的个数
            if (sum > orders)
            {
                return true;
            }
        }
        return false;
    }
};

int gcd(int a, int b)
{
    while (b != 0)
    {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}
int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}
