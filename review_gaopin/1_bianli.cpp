#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
void array_bianli_example(const std::vector<int> &arr)
{
    // 一维全元素遍历
    for (int i = 0; i < arr.size(); ++i)
    {
        std::cout << arr[i] << std::endl;
    }
    // 遍历所有的[i,j]对，其中i<=j
    for (int i = 0; i < arr.size(); ++i)
    {
        for (int j = i; j < arr.size(); ++j)
        {
        }
    }
    // 遍历固定长度的连续子数组,j-i+1才是i,j之间的距离
    int length = 3;
    for (int i = 0; i + length - 1 < arr.size(); ++i)
    {
        for (int j = i + length - 1; j >= i; j--)
        {
        }
    }
    // 遍历所有的子集，即不需要连续
    int size = arr.size();
    for (int mask = 0; mask < (1 << size); mask++)
    {
        // 遍历这个二进制数的每一位
        for (int i = 0; i < size; ++i)
        {
            int bit = mask & (1 << i);
            if (bit == 1)
            {
                std::cout << arr[bit] << '\n';
            }
        }
    }

    // 滑动窗口求最大子数组和
    int max_sum = INT_MIN;
    int window_sum = 0;
    for (int i = 0; i < arr.size(); ++i)
    {
        window_sum = std::max(arr[i], window_sum + arr[i]); // 选择扩展窗口或重新开始新的窗口
        max_sum = std::max(max_sum, window_sum);            // 记录当前找到的最大子数组和
    }
    std::cout << max_sum << '\n';
}

void permute(std::vector<int> &nums, std::vector<bool> &used, std::vector<int> &current, std::vector<std::vector<int>> &result)
{
    if (current.size() == nums.size())
    {
        result.push_back(current);
        return;
    }
    for (int i = 0; i < nums.size(); ++i)
    {
        if (!used[i])
        {
            used[i] = true;
            current.push_back(nums[i]);
            permute(nums, used, current, result);
            current.pop_back();
            used[i] = false;
        }
    }
}

// 排序，取start+1,保证纵向遍历到的是当前点的右侧
void combine(std::vector<int> &nums, int start, int k, std::vector<int> &current, std::vector<std::vector<int>> &result)
{
    if (current.size() == k)
    {
        result.push_back(current);
        return;
    }
    for (int i = start; i < nums.size(); ++i)
    {
        current.emplace_back(nums[start]);
        combine(nums, i + 1, k, current, result);
        current.pop_back();
    }
}

int main()
{
    return 0;
}