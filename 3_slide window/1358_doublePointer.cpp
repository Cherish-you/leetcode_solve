#include <iostream>
#include <string>

using namespace std;

int get(string str)
{
    int cnt[3]{0};
    int ans = 0;
    int n = str.length();
    int left = 0;
    for (int right = 0; right < n; right++)
    {
        // if (right == n-1 && left < right - 2)
        // {
        //     right--;
        // }
        // else
        // {
        //     cnt[str[right] - 'a']++;
        // }//这样行不通，存在逻辑错误
        cnt[str[right] - 'a']++;

        while (cnt['a' - 'a'] >= 1 && cnt['b' - 'a'] >= 1 && cnt['c' - 'a'] >= 1)
        {
            ans = ans + (n - right);
            cnt[str[left] - 'a']--;
            left++;
        }//一次性找完，直到窗口收缩到最小
    }
    return ans;
}

int main()
{

    string str;
    cout << "enter the string: " << endl;
    cin >> str;
    cout << get(str) << endl;

    return 0;
}