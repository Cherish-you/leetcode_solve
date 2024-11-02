#include <iostream>
#include <climits>
#include <vector>
#include <bits/ranges_algo.h>
using namespace std;

int get(int num[], int n)
{                                 // 特别注意这里的初始值和顺序的问题
    int max_prefix_sum = INT_MIN; // 给最小值是为了让首次一定是更新
    int prefix_sum = 0;           // 初始给0，因为它最先赋值
    int min_prefix_sum = 0;       // 初始给0是为了使s[0]-min_prefix_sum=num[0]，但由于0本身不存在，放到前面会左右结果
//!因为要求的是连续子数组的和最大 当前前缀和，最小前缀和都是左端不动，能包含到所有的情况 

    for (int i = 0; i < n; i++)
    {
        prefix_sum = prefix_sum + num[i];                                  // 枚举所有前缀和
        max_prefix_sum = max(max_prefix_sum, prefix_sum - min_prefix_sum); // 记录（前缀和-最小前缀和）的最大值
        min_prefix_sum = min(prefix_sum, min_prefix_sum);                  // 记录前缀和的最小值
    }
    return max_prefix_sum;
}
// 不能直接找nums的最大前缀和最小前缀做差的，因为不能保证索引上大，故固定一端

//以i结尾的最大前缀和
int get_2(int nums[], int n)
{
    int f[n] = {0};
    f[0] = nums[0];
    for (int i = 1; i < n; ++i)
    {
        f[i] = max(f[i - 1], 0) + nums[i];
    }

    int max = INT_MIN;
    for (int j = 0; j < n; ++j)
    {
        max = max > f[j] ? max : f[j];
    }
    return max;
}

int main()
{
    int nums[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << get(nums, n) << endl;
    cout << get_2(nums, n) << endl;

    return 0;
}