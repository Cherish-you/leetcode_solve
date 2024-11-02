#include <iostream>
#include <vector>
#include <math.h>

// 461 //! 异或特性：可以保留两方中仅有一方有的部分
int hammingDistance(int x, int y)
{
    // 1
    // return __builtin_popcount(x ^ y);

    // 2
    //  int s=x^y,ret=0;
    //  while(s) {
    //      ret=ret+(s&1);//! s&1可得到最低位的值
    //      s=s>>1;
    //  }
    //  return ret;

    // 3
    int s = x ^ y, ret = 0;
    while (s)
    {
        s = s & (s - 1); //! 将右侧第一个1变为0
        ret++;
    }
    return ret;
}

// 338
int numsOf_1(int n)
{
    int ret = 0;

    while (n)
    {
        n = n & (n - 1);
        ret++;
    }
    return ret;
}

std::vector<int> get(int n)
{
    std::vector<int> vec(n + 1, 0);
    for (int i = 0; i <= n; ++i)
    {
        vec[i] = numsOf_1(i);
    }
    return vec;
}

std::vector<int> get_2(int n)
{
    std::vector<int> vec(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        if (i & 1)
        { // 奇数
            vec[i] = vec[i - 1] + 1;
        }
        else
        {
            vec[i] = vec[i / 2];
        }
    }
    return vec;
}

// 1318 //! 或的特性 or的数越多，结果越大
int minFlips(int a, int b, int c)
{
    int res = 0;

    for (int i = 0; i < 31; ++i)
    {
        int bit_a = (a >> i) & 1; //! 右移i位，取最低位，就是第i位
        int bit_b = (b >> i) & 1;
        int bit_c = (c >> i) & 1;

        if (bit_c == 0)
        {
            res = res + bit_a + bit_b;
        }
        else
        {
            int tmp = (bit_a | bit_b) ? 0 : 1;
            res = res + tmp;
        }
    }
}

// 2419 //! 与的特性，与的结果小于等于作与的最大值 and的数越多，结果越小
int LongestSubNum(int nums[], int size)
{
    // int ret=0;
    // int left=-1;
    // for(int right=0;right<size;right++) {
    //     int tmp=
    //     ret=std::max(ret,tmp);

    //     while()
    // }//滑动窗口失败

    int max_num = 0;
    for (int i = 0; i < size; i++)
    {
        max_num = std::max(max_num, nums[i]);
    }

    int ans = 0;
    int res = 0; //! 利用遍历的天然有序性得到该值连续出现的最大次数
    for (int i = 0; i < size; ++i)
    {
        if (nums[i] == max_num)
        {
            ans++;
            res = std::max(res, ans);
        }
        else
        {
            ans = 0;
        }
    }
}