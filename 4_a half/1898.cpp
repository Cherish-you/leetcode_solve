#include <iostream>
#include <string>

using namespace std;

// 二分 适用于变量有范围，求变量在满足某条件下的最值问题
// 这个条件就是二分更新的条件，
bool canRemove(string s, const string &p, int remove[], int k)
{
    for (int i = 0; i < k; i++)
    {
        s.erase(remove[i], 1);
    }
    int length = p.length();
    if (s.length() < length)
    {
        return false;
    }
    for (int j = 0; j < length; j++)
    {
        if (s.find(p[j]) == string::npos)
        {
            return false;
        }
    }
    return true;
}

int get(const string &s, const string &p, int remove[], int size)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (canRemove(s, p, remove, mid))
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return right;
}

int main()
{
    string s = "abcbddddd";
    string p = "abcd";
    int remove[] = {3, 2, 1, 4, 5, 6};
    int size = sizeof(remove) / sizeof(remove[0]);
    cout << get(s, p, remove, size) << endl;
    return 0;
}