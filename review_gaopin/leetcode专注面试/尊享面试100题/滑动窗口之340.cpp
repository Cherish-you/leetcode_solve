#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/*要找至多包含k种字符的最长子串：
思路：首先连续的子串想到滑动窗口，
窗口容器要求可以指出元素种类和元素个数（有个数才能看这个元素是不是彻底出去了），不必有序，unordered_map*/
int lengthOfLongest(string s, int k)
{
    int length = s.size();

    int left = 0;
    int maxLen = 0;
    unordered_map<char, int> umap;
    for (int i = 0; i < length; ++i)
    {
        umap[s[i]]++;
        while (umap.size() > k)
        { // 不满足时候缩小窗口
            umap[s[left]]--;
            left++;
            if (umap[s[left]] == 0)
            {
                umap.erase(s[left]);
            }
        }
        maxLen = max(maxLen, i - left + 1);
    }
    return maxLen;
}

int main()
{
    string s;
    int k;
    cin >> s >> k;
}