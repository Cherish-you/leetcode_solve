#include <iostream>
// todo 有些许不解，但类比暴力的i，j的变化 可知是先计数再更新

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
} // 最大公因数，用于判断是否互质

// 最小公倍数
int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

int solve(int nums[], int n)
{
    int count = 0;
    int frequency[10] = {0};
    for (int i = 0; i < n; ++i)
    {
        for (int y = 1; y <= 9; y++)
        {
            if (frequency[y] && gcd(nums[i] % 10, y) == 1) // 截取最低位
            {
                count = count + frequency[y];
            }
        }
        int n = nums[i];
        while (n >= 10)
        {
            n = n / 10;
        } // 截取最高位
        frequency[n]++;
    }
    return count;
}

int main()
{
}