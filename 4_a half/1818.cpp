#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

#define MOD 1000000007

using namespace std;

// int lower_bound(const vector<int> &vec, int target)
// {
//     int l = 0;
//     int r = vec.size() - 1;
//     while (l <= r)
//     {
//         int mid = l + (r - l) / 2;
//         if (vec[mid] < target)
//             l = mid + 1;
//         else
//             r = mid - 1;
//     }
//     return r + 1;
// }

int get(const vector<int> &v1, const vector<int> &v2)
{
    vector<int> vec(v1);
    int sum = 0;
    int maxn = 0;
    sort(vec.begin(), vec.end());
    int n = v1.size();
    for (int i = 0; i < n; i++)
    {
        int diff = abs(v1[i] - v2[i]);
        sum = (sum + diff) % MOD;//计算sum
        int j = lower_bound(vec.begin(), vec.end(), v2[i]) - vec.begin();//统计最大的|v1[i]-v2[i]|-|v1[j]-v2[i]|
        if (j < n)
        {
            maxn = max(maxn, diff - abs(vec[j] - v2[i]));
        }
        if (j > 0)
        {
            maxn = max(maxn, diff - abs(v2[i] - vec[j - 1]));
        }
    }
    return (sum - maxn + MOD) & MOD;
}

int main()
{
    return 0;
}