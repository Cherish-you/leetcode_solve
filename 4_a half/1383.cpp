#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int get(vector<int> vec, int threshold)
{
    int size = vec.size();

    int left = 1;
    int right = *max_element(vec.begin(), vec.end());
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum = sum + ((vec[i] - 1) / mid + 1);
        }
        if (sum <= threshold)
        {
            right = mid - 1;
        }
        else
            left = mid + 1;
    }
    return right+1;
}


int main()
{
    return 0;
}