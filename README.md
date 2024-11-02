they are some solutions of leetcode 

now it have 
leetcode 刷题注意事项： 0_guide
数组，链表双指针；
https://labuladong.online/algo/essential-technique/linked-list-skills-summary/#%E5%8D%95%E9%93%BE%E8%A1%A8%E7%9A%84%E5%88%86%E8%A7%A3
https://labuladong.online/algo/essential-technique/array-two-pointers-summary/

双变量：暴力双层for的i，j的变化逻辑上等价，和一次遍历实现双变量的查找返回（将已遍历到的部分放入哈希表，来查找）   1_double variable

前缀和数组和差分数组：（可在o（1）时间内完成对连续子序列（子矩阵）的求和或进行一次+-val的运算）  2_prefixSumandDifferenceArray

滑动窗口模板：
int left = 0, right = 0;
while (right < nums.size()) {
    // 增大窗口
    window.addLast(nums[right]);
    right++;
    //进行窗口内数据的更新
    
    while (window needs shrink) {
        // 缩小窗口
        window.removeFirst(nums[left]);
        left++;
    }
    //进行窗口内数据的更新
}

二分查找解决的是:为满足条件（check），某个区间内变量具体取什么值或最值的问题
int binarySearch(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;//以端点闭区间为例
    while (left<=right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            ...
        } else if (nums[mid] < target) {
            left = ...
        } else if (nums[mid] > target) {
            right = ...
        }
    }
}

位运算（提高算术的速率）：


栈：
单调栈是为了：当前元素寻找相邻元素满足某条件的第一个元素
// 从顶向下看：单调递增栈模板,     希望保留相同的元素在栈中就不加=，否则加=
int monotoneIncreasingStack(int nums[], int size)
{
    stack<int> st; // 一般存下标，下标比元素本身具备更多的信息

    for (int i = 0; i < size; ++i)
    {
        while (!st.empty() && nums[i] >= nums[st.top()])
        {
            st.pop();
        }
        st.push(i);
    }
}

二叉树：
遍历和分解问题


图：
多叉树的遍历/层序遍历 


