#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// 这里的巧妙在于数组遍历的天然相邻性，解决了相邻的大问题
bool isMake(const vector<int> &vec, int day, int m, int k)
{
    int shu = 0;
    int duo = 0;

    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] <= day)
        {
            duo++;
            if (duo == k)
            {
                shu++;
                duo = 0;
            }
        }
        else
        {
            duo = 0;
        }
    }
    return shu >= m;
}

int get(const vector<int> &vec, int m, int k)
{
    if (vec.size() < m * k)
        return -1;
    int left = -1;
    int right = -1;
    for (int i = 0; i < vec.size(); i++)
    {
        left = min(left, vec[i]);   // 最小天数
        right = max(right, vec[i]); // 最大天数
    }

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (isMake(vec, mid, m, k))
        {
            right = mid - 1;
        }
        else
            left = mid + 1;
    }
    return right + 1;
}

int main()
{
    vector<int> vec = {7, 7, 7, 7, 12, 7, 7};
    int m = 2;
    int k = 3;
    cout << get(vec, m, k) << endl;

    return 0;
}