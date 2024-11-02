#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <string_view>

using namespace std;

int get(const string &str, int k)
{
    int res = 0;
    int tmp = 0;
    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
        {
            tmp++;
        }
        if (i < k - 1)
        {
            continue;
        }
        res = max(res, tmp);
        if (str[i - k + 1] == 'a' || str[i - k + 1] == 'e' || str[i - k + 1] == 'i' || str[i - k + 1] == 'o' || str[i - k + 1] == 'u')
        {
            tmp--;
        }
    }
    return res;
}

// 1984
int get_(int nums[], int size, int k)
{
    // int size = sizeof(nums) / sizeof(nums[0]);//在外面写就是计算数组大小
    //'sizeof' on array function parameter 'nums' will return size of 'int*

    sort(nums, nums + size);

    int res = INT_MAX;
    int tmp = 0;
    for (int i = 0; i < size; ++i)
    {
        if (i < k - 1)
            continue;
        tmp = nums[i] - nums[i - k + 1];
        res = min(res, tmp);
    }
    return res;
}

// 2953
int getCount(string_view str, int k);//前置声明

int countCompleteSubstrings(string str, int k)
{

    int n = str.length();
    string_view s(str); // 是一种轻量的字符串引用方式 c++17
    int ans = 0;
    for (int i = 0; i < n;)//截取满足的序列
    {
        int st = i;
        for (i++; i < n && abs(static_cast<int>(s[i] - s[i - 1])) <= 2; ++i)
            ;
        string_view sub = s.substr(st, i - st);
        ans = ans + getCount(sub, k);
    }
    return ans;
}

int getCount(string_view str, int k)
{
    int res = 0;                                           // 计数值
    for (int i = 1; i <= 26 && i * k <= str.length(); i++) // 每一次循环中点出了窗口的大小i*k
    {
        int cnt[26]{};
        auto check = [&]()
        {
            for (int i = 0; i < 26; i++)
            {
                if (cnt[i] && cnt[i] != k)
                { //
                    return;
                }
            }
            res++;
        };
        for (int right = 0; right < str.length(); right++)
        {
            cnt[str[right] - 'a']++;
            int left = right - i * k + 1;
            if (left >= 0)
            {
                check();
                cnt[str[left] - 'a']--;
            }
        } // 窗口记录的信息：窗口内每个字母出现的次数
    }
    return res;
}

int main()
{
    string str = "";
    cout << "enter the string: " << '\n';
    cin >> str;
    cout << str << endl;
    int k;
    cout << "enter the length of the substring: " << '\n';
    cin >> k;

    cout << countCompleteSubstrings(str, k) << endl;

    return 0;
}