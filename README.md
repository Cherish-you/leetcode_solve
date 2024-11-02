they are some solutions of leetcode 

now it have 
leetcode 刷题注意事项： 0_guide
数组，链表双指针；
https://labuladong.online/algo/essential-technique/linked-list-skills-summary/#%E5%8D%95%E9%93%BE%E8%A1%A8%E7%9A%84%E5%88%86%E8%A7%A3
双变量：一次遍历实现双变量的查找返回（将已遍历到的部分放入哈希表，来查找） 1_double variable
前缀和数组和差分数组：（可在o（1）时间内完成对连续子序列（子矩阵）的求和或进行一次+-val的运算）
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

