#include <iostream>
// #include <string>
#include <unordered_map>

using namespace std;
int getNum(int nums[], int size, int k)
{

    unordered_map<int, int> mp;
    int ans = 0;
    int left = 0;
    for (int right = 0; right < size; right++)
    {
        // mp[nums[right]]++;
        // if (mp.size() == k)
        // { // 此时恰好为k
        //     ans++;
        //     auto it = mp.find(nums[right + 1]);
        //     if (it == mp.end())
        //     { // 下一个元素不在map中，此时要移动窗口
        //         if (--mp[nums[left++]] == 0)
        //         {
        //             mp.erase(nums[left]);
        //         }
        //     }
        // }
    }
}
int get(int nums[],int size,int k) {

    unordered_map<int,int> mp;
    int ans=0;//answer
    int diff=0;//num of different numbers
    int left=0;
    for(int right=0;right<size;right++) {
        if(mp[nums[right]]==0) {
            diff++;
        }
        mp[nums[right]]++;
        while(diff>k) {
            if(--mp[nums[left++]]==0) {
                diff--;
                mp.erase(nums[left-1]);
            }
        }
        ans=ans+right-left+1;
    }
    return ans;
}
int main()
{

    return 0;
}