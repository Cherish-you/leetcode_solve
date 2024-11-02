#include <iostream>
#include <vector>

#include <map>

using namespace std;

long long kthSmallestProduct(vector<int> &nums1, vector<int> &nums2, long long k)
{
    multimap<long long, int> mp;
    int size_1 = nums1.size();
    int size_2 = nums2.size();
    
    for (int i = 0; i < size_1; ++i)
    {
        for (int j = 0; j < size_2; ++j)
        {
            mp.insert(make_pair(static_cast<long long>(nums1[i]) * static_cast<long long>(nums2[j]), 0));
        }
    }
    auto it = mp.begin();
    advance(it, k - 1);
    if (it != mp.end())
    {
        return it->first;
    }
    return -1;
}

int main()
{

    return 0;
}