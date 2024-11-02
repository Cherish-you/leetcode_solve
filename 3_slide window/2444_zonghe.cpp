#include <iostream>
#include <map>

using namespace std;

int get(int nums[], int size, int mink, int maxk)
{

    map<int, int> mp;

    int ans = 0;
    int left = 0;
    int min_tmp, max_tmp;
    for (int right = 0; right < size; right++)
    {
        mp[nums[right]]++;
        if (nums[right] == mink)
        {
            min_tmp = right;
        }
        if (nums[right] == maxk)
        {
            max_tmp = right;
        }

        while (mp.begin()->first == mink && mp.rbegin()->first == maxk)
        {
            if (nums[right] == mp.begin()->first)
            {
                ans = ans + min_tmp - left;
            }
            else if (nums[right] == mp.rbegin()->first)
            {
                ans = ans + max_tmp - left;
            }
            else
            {
            }
        }
    }
} // 卒
// others thoughts
int getIt(int nums[], int size, int mink, int maxk)
{
    int min_tmp = -1; // 索引的初始值一般为-1，因为0是有意义的
    int max_tmp = -1;
    int ans = 0;
    int non_satisfaction = -1;

    for (int i = 0; i < size; i++)
    {
        if (nums[i] == mink)
        {
            min_tmp = i;
        }
        if (nums[i] == maxk)
        {
            max_tmp = i;
        }
        if (nums[i] > maxk || nums[i] < mink)
        {
            non_satisfaction = i;
        }
        ans = ans + max(min(min_tmp, max_tmp) - non_satisfaction, 0); // 为什么满足的是这些，看数轴示意图
    }
}
int main()
{

    return 0;
}