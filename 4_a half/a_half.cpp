#include <stdio.h>

using namespace std;

// 二分的模板 解决的是 为满足条件（check），某个区间内变量具体取什么值的问题

// 左闭右闭
int lower_bound_1(int nums[], int size, int target)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else
            right = mid - 1;
    }
    return right + 1;
}

// 左闭右开
int lower_bound_2(int nums[], int size, int target)
{
    int left = 0;
    int right = size;

    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return right;
}

// 左开右开，这个返回值我不是很清楚，推荐使用第一种
int lower_bound_3(int nums[], int size, int target)
{
    int left = -1;
    int right = size;

    while (left < right - 1)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
            left = mid;
        else
            right = mid;
    }
    return right;
}

int main()
{
    int nums[] = {5, 7, 7, 8, 8, 10};
    int size = sizeof(nums) / sizeof(nums[0]);
    int target = 8;

    int res_1 = lower_bound_1(nums, size, target);
    int res_2 = lower_bound_2(nums, size, target);
    int res_3 = lower_bound_3(nums, size, target);
    printf("res_1=%d\n", res_1);
    printf("res_2=%d\n", res_2);
    printf("res_3=%d\n", res_3);
    return 0;
}