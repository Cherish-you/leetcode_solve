#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
// #include <vector>
#include <queue>
#include <map>

using namespace std;

//滑动窗口模板：
/*
int n=s.length();
map<int,int> mp; //根据需要的特性，有一个容器物理上或者直接逻辑上来存窗口
int left=0;
for(int right=0;right<n;++right) {
    //*更新窗口
    mp[s[right]]++;
    //*收缩窗口来持续满足条件
    while(条件) {
        //*更新窗口
        mp[s[left]]--;
        left++;
    }
    //*更新结果
    }

*/



int lengthOfLongestSubstring(string s)
{
    int n = s.length();
    unordered_set<char> window;
    // unordered_set is a set that does not allow duplicate values and does not maintain any order
    //*虽然容器无序，但维护了left来记录左边界，right是右边界 可以做到顺序插删
    int left = 0;
    int ans = 0;
    for (int right = 0; right < n; right++)
    {
        while (window.count(s[right]))
        {
            window.erase(s[left++]);
        }
        window.insert(s[right]);
        ans = max(ans, right - left + 1);
    }
    return ans;
}

// 1438
//! 不能直接给原数组排序，这样造成了原数组的改变
// int getLongest(int nums[], int size, int limit)
// {

//     // sort(nums, nums + size);

//     // for (int i = 0; i < size; i++)
//     // {
//     //     cout << "nums" << nums[i] << " ";
//     // }
//     // cout << endl;
//     queue<int> qu;
//     int left = 0;
//     int ans = 0; // answer

//     for (int right = 0; right < size; right++)
//     {
//         if (abs(nums[right] - nums[left]) <= limit)
//         {
//             qu.push(nums[right]);
//         }
//         ans = max(ans, (int)qu.size());
//         while (abs(nums[right] - nums[left]) > limit)
//         {
//             qu.pop();
//             left++;
//         }
//     }
//     return ans;
// }

// true
int getLongest_true(int nums[], int size, int limit)
{

    map<int, int> cnt; // 键表示nums的值，值表示该值出现的次数   按键升序
    int ans = 0;
    int left = 0;
    for (int right = 0; right < size; right++)
    {
        cnt[nums[right]]++;
        while (cnt.rbegin()->first - cnt.begin()->first > limit)
        { // 利用map的键有序性，找到窗口中的最大值和最小值
            if (--cnt[nums[left++]] == 0)
            { // 引用值减1，窗口左移
                cnt.erase(nums[left - 1]);
            }
        }
        ans = max(ans, right - left + 1);
    }
    return ans;
}

int main()
{
    cout << "enter the nums and the limits:" << endl;
    string str = "";
    int nums[100] = {-1};
    int index = 0;
    getline(cin, str);
    for (int i = 0; i < str.length(); i++)
    {
        string tmp = "";
        if (isdigit(str[i]))
        {
            tmp = str[i];
            i++;
            while (isdigit(str[i]) && i < str.length())
            {
                tmp += str[i];
                i++;
            }
            nums[index++] = stoi(tmp);
        }
    }

    cout << getLongest_true(nums, index - 1, nums[index - 1]) << endl;
}