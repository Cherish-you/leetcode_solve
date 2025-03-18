#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

struct ListNode
{
    int data;
    struct ListNode *next;
    ListNode()
    {
    }
    ListNode(int data)
    {
        this->data = data;
        next = nullptr;
    }
};

struct ListNode *insert(struct ListNode *head, int ind, struct ListNode *a)
{
    struct ListNode ret;
    struct ListNode *p = &ret;
    ret.next = head;

    while (ind--)
    {
        p = p->next;
    }
    a->next = p->next;
    p->next = a;
    return ret.next;
}

class Solution_list
{
public:
    /*
    链表操作提醒：
    有一个空节点作为首个节点，但不会暴露出来，也就是给一个链表给的都是实头节点；有空节点可以统一操作，更方便
    不要使用链表原有的指针，应该另外创建指针去指向head去操作
    记得两种情况要判定：p不为空才有p->next；p->next不为空才有p->next->next
    做链表的题在脑海里构建示意图: dummy->口->口->口,初始p指向头节点，然后开始操作*/
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        ListNode dummy(-1);
        ListNode *p = &dummy;
        ListNode *p1 = l1;
        ListNode *p2 = l2;

        while (p1 != nullptr && p2 != nullptr)
        {
            if (p1->data < p2->data)
            {
                p->next = p1;
                p1 = p1->next;
            }
            else if (p1->data >= p2->data)
            {
                p->next = p2;
                p2 = p2->next;
            }
            p = p->next;
        }
        if (p1 != nullptr)
        {
            p->next = p1;
        }
        if (p2 != nullptr)
        {
            p->next = p2;
        }
        return dummy.next;
    }

    //*以给定数划分链表，要求保持相对位置不变
    /*关键是如何在已知链表上摘掉任意一个节点：要摘，就要知道pre,统一逻辑就需要在head前人为加一个虚拟节点；摘和不摘pre，p的变化是不一样的*/
    ListNode *fenGeList(ListNode *head, int x)
    {
        if (head == nullptr)
            return nullptr;

        ListNode ori_dummy(-1);
        ListNode *oriList = &ori_dummy;
        oriList->next = head;
        ListNode *pre = oriList, *p = oriList->next; // 自行穿入一个虚拟头节点

        // 新链表
        ListNode dummy(-1);
        ListNode *newList = &dummy;
        ListNode *weibu = newList;
        while (p != nullptr)
        {
            if (p->data < x)
            {
                pre->next = p->next; // 从原链表上摘下来，摘下来的这个节点由p指向
                p->next = nullptr; // 破除原来的连接
                
                //头插法
                // p->next=newList->next;//将p加到新链表上
                // newList->next=p;//这是头插，但结果是尾插
                //尾插法
                weibu->next = p;
                weibu = p;

                p = pre->next;
            }
            // 错误原因：逻辑有问题，摘掉之后，应该pre不动，只有p动
            else
            { // 不摘才是pre,p一起动,发现可以统一逻辑，之前的判断也没有意义了
                pre = pre->next;
                p = pre->next;
                // if (pre == nullptr)
                // {
                //     p = pre;
                // }
                // else
                // {
                //     p = pre->next;
                // }
                
            }
        }
        ListNode *newp = newList->next;
        if (newp != nullptr)
        {
            while (newp->next != nullptr)
            {
                newp = newp->next;
            }
            newp->next = oriList->next;
            return newList->next;
        }
        else
        {
            return oriList->next;
        }
    }

    /*获取倒数第k个节点，让两个指针保持k的距离，这样一个到达终点，另一个就是倒数第k个*/
    ListNode *findFromEnd(ListNode *head, int k)
    {
        ListNode *p1 = head;
        for (int i = 0; i < k; ++i)
        {
            p1 = p1->next;
        }
        ListNode *p2 = head;
        while (p1 != nullptr)
        {
            p1 = p1->next;
            p2 = p2->next;
        }
        return p2;
    }

    // 返回中点
    ListNode *middleNode(ListNode *head)
    {
        // 快慢指针初始化指向 head
        ListNode *slow = head;
        ListNode *fast = head;
        // 快指针走到末尾时停止
        while (fast != nullptr && fast->next != nullptr)
        {
            // 慢指针走一步，快指针走两步
            slow = slow->next;
            fast = fast->next->next;
        }
        // 慢指针指向中点
        return slow;
    }

    // 判断是否有环
    int hasCycle(struct ListNode *head)
    {
        if (head == NULL)
        { // 不为空next才有意义
            return 0;
        }
        struct ListNode *p = head;
        struct ListNode *q = head;
        while (q != nullptr && q->next != nullptr)
        {
            q = q->next->next;
            p = p->next;
            if (p = q)
            {
                return true;
            }
        }
        return false;
    }
};

/*二分思维的精髓就是：
通过已知信息尽可能多地收缩（折半）搜索空间，从而增加穷举效率，快速找到目标。*/
int binarySearch(const std::vector<int> &nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] > target)
        { // 最终right往右全部满足这个条件
            right = mid - 1;
        }
        else if (nums[mid] < target)
        { // 最终left往左全部满足<target
            left = mid + 1;
        }
        else if (nums[mid] == target)
        { //* 查找target的左边界,不直接返回
            right = mid - 1;
        }
    }
    return nums[left] == target ? left : -1; // 没有的情况下left表示的是大于target的第一个值
}
// 查找target的右边界
int binarySearch_2(const std::vector<int> &nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] > target)
        {
            right = mid - 1;
        }
        else if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else if (nums[mid] == target)
        {
            left = mid + 1;
        }
    }
    return nums[right] == target ? right : -1; // 没找到
}

/*统计具体的s[i,j]中是否存在t,使用vector<char> vec(128,0)，各自遍历一遍填写，然后再遍历这个vector或
确定两个unordered_map是否相等（==运算符或者std::equal()或者遍历实现）：
for (const auto& pair : a) {
    auto it = b.find(pair.first);
    if (it == b.end() || it->second != pair.second) {
        return false;
    }
}
*/
/*滑动窗口：解决数组中满足某条件最优的子数组问题，比如让你寻找符合某个条件的最长/最短子数组。
三个问题：
1、什么时候应该扩大窗口？

2、什么时候应该缩小窗口？

3、什么时候应该更新答案？
*/
void slidingWindow(string s)
{ // 用合适的数据结构表示窗口
    // 比如记录出现次数，用unordered_map
    // 记录窗口中是否出现某个元素，用unordered_set,
    // 记录窗口中元素的和，用一个int
    unordered_set<char> windows;

    int left = 0;
    int right = 0; // 这是左闭右开的
    // 1.外部记录解的变量result
    while (right < s.size())
    {
        char c = s[right];
        windows.insert(c);
        right++; // 2.进入窗口

        // // debug位置
        // printf("windows: [%d,%d]]\n", left, right);

        while (/*need shrink*/ true)
        { // 3.缩窗口(注意：原因可能是找到了解，也可能是没找到解超过长度而收缩)

            /*
            if(目前这个窗口是我们要的解)
                 result=max(result,right-left+1);
            */

            char d = s[left];
            windows.erase(d);
            left++;
        }
    }
    // return result 4.最终返回最优解
}
// 举例：
class SolutionForWindow
{
public:
    /*1.最小覆盖子串：给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。
    如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 */
    string minWindow(string s, string t)
    {
        unordered_map<char, int> need, windows;
        for (int i = 0; i < t.length(); ++i)
        {
            need[t[i]]++;
        }

        int left = 0;
        int right = 0;

        int validNum = 0; // 窗口中有效的字母数,当等于need.size()时说明完全覆盖
        int start, len = INT_MAX;
        while (right < s.size())
        {
            char c = s[right];
            right++;

            if (need.count(c))
            { // 首先这个字符是出现过的，其次和need[c]值一样
                windows[c]++;
                if (windows[c] == need[c])
                    validNum++;
            }

            while (validNum == need.size())
            {
                if (right - left < len)
                {
                    start = left;
                    len = right - left;
                }
                char d = s[left];
                left++;
                if (need.count(d))
                {
                    if (windows[d] == need[d])
                    {
                        validNum--;
                    }
                    windows[d]--;
                }
            }
        }
    }

    /*2.字符串排列：给你两个字符串 s1 和 s2 ，判断 s2 是否包含 s1 的排列。
    如果是，返回 true ；否则，返回 false 。即s1的排列之一是s2的子串*/
    bool permuteOfString(string s1, string s2)
    {
        unordered_map<char, int> need, windows;
        for (int i = 0; i < s1.length(); ++i)
        {
            need[s1[i]]++;
        }

        int left = 0;
        int right = 0;
        int validNum = 0;
        while (right < s2.size())
        {
            char c = s2[right];
            if (need.count(c))
            {
                windows[c]++;
                if (need[c] == windows[c])
                {
                    validNum++;
                }
            }
            right++;

            while (right - left >= s1.size())
            { // 当前窗口中的元素大于等于给定字符串长度时要收缩，因为是包含它的排列，且
                // 且因为左闭右开，所以长度是right-left
                if (validNum == need.size())
                {
                    return true;
                }
                char d = s2[left];
                if (need.count(d))
                {
                    if (windows[d] == need[d])
                    {
                        validNum--;
                    }
                    windows[d]--;
                }
                left++;
            }
            return false;
        }
    }

    /*3.找到字符串中所有字母异位词：
    给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，
    异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。
    返回这些子串的起始索引。不考虑答案输出的顺序。
    */
    vector<int> get(string s, string p)
    {
        unordered_map<char, int> need, windows;
        for (char ch : p)
        {
            need[ch]++;
        }

        int left = 0;
        int right = 0;
        int validNum = 0;
        vector<int> result;
        while (right < s.size())
        {
            char c = s[right];
            if (need.find(c) != need.end())
            {
                windows[c]++;
                if (need[c] == windows[c])
                {
                    validNum++;
                }
            }
            right++;

            while (right - left >= p.size())
            {
                if (validNum == need.size())
                {
                    result.push_back(left);
                }
                if (need.count(s[left]))
                { // 这个元素是有关的
                    if (windows[s[left]] == need[s[left]])
                    { // 这个元素影响有效的个数
                        validNum--;
                    }
                    windows[s[left]]--;
                }
                left++;
            }
        }
        return result;
    }
    /*4.无重复字符的最长子串,
    //!这个写的有问题，还没有找到在哪里
    给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。
    */
    int getMaxSubLength(string s)
    {
        int left = 0;
        int right = 0;
        unordered_set<char> windows;
        int MaxLength = 0;
        bool manzu = true;
        while (right < s.size())
        {
            char c = s[right];
            if (windows.count(c))
            {
                MaxLength = max(MaxLength, right - 1 - left);
                manzu = false;
            }
            else
            {
                windows.insert(c);
            }
            right++; // 2.进入窗口

            while (!manzu)
            { // 3.缩窗口(注意：原因可能是找到了解，也可能是没找到解超过长度而收缩)

                char d = s[left];
                windows.erase(d);
                left++;
                if (windows.count(c) == 1)
                { // 由于某一个元素的进入导致的重复直到该元素只剩一个时停下
                    manzu = true;
                }
            }
        }
        return MaxLength;
    }
};

int main()
{

    return 0;
}