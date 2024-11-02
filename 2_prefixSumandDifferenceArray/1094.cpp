#include <vector>
#include <iostream>

using namespace std;

/*车上最初有 capacity 个空座位。车 只能 向一个方向行驶（也就是说，不允许掉头或改变方向）

给定整数 capacity 和一个数组 trips ,  trip[i] = [numPassengersi, fromi, toi] 表示第 i 次旅行有 numPassengersi 乘客，接他们和放他们的位置分别是 fromi 和 toi 。这些位置是从汽车的初始位置向东的公里数。

当且仅当你可以在所有给定的行程中接送所有乘客时，返回 true，否则请返回 false。*/

bool isTripAll(int capacity, vector<vector<int>> &trips)
{

    // int diff[1001] = {0}; // 由于原数组就是0，所以差分数组也全是0
    // 优化一下大小 为最大的结束位置+1
    int max_end = 0;
    for (const auto &trip : trips)
    {
        max_end = max(trip[2], max_end);
    }
    int len = max_end + 1;
    int diff[len] = {0};

    int size = trips.size();
    for (int i = 0; i < size; ++i)
    {
        int val = trips[i][0];
        int start = trips[i][1];
        int end = trips[i][2];
        diff[start] += val;
        if (end + 1 < 1001)
        {
            diff[end + 1] -= val;
        }
    }

    int count = 0; // 原则上只需要计算一个原始值就行了，没必要都算，
    for (int i = 0; i < len; ++i)
    {
        count = count + diff[i];
        if (count > capacity)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int capacity = 4;
    vector<vector<int>> trips = {{2, 1, 5}, {3, 3, 7}};
    bool result = isTripAll(capacity, trips);
    cout << "result: " << result << endl;
    return 0;
}