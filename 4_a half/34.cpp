#include <iostream>

using namespace std;

int get(int nums[], int size, int target)
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

void real(int nums[], int size, int target)
{
    if (nums == NULL || size <= 0)
    {
        cout << "[-1,-1]" << endl;
    }
    int first = get(nums, size, target);        // 拿到第一个大于等于target的数
    int last = get(nums, size, target + 1) - 1; // 拿到最后一个大于等于target的数
    if (nums[first] == target && nums[last] == target)
    {
        cout << "[" << first << "," << last << "]" << endl;
    }
    else
    {
        cout << "[-1,-1]" << endl;
    }
}

int main()
{
    int nums[]{}; // 空数组，大小为0
    int size = sizeof(nums) / sizeof(nums[0]);
    int target = 0;
    real(nums, size, target);
    return 0;
}