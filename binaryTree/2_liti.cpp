#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <unordered_map>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
// 104 二叉树最大深度

// 1.遍历一遍二叉树，用一个外部变量记录每个节点所在的深度，取最大值就可以得到最大深度
//! 思考点：需要维护什么变量（给成全局量/参数） 终止条件
class Solution1
{
public:
    int res = 0;
    int depth = 0; // 全局量，意味着需要撤销操作

    int maxDepth(TreeNode *root)
    {
        traverse(root);
        return res;
    }

private:
    void traverse(TreeNode *root)
    {
        if (root == nullptr)
            return;
        depth++; // 即将进入这个节点时进行的操作
        if (root->left == nullptr && root->right == nullptr)
        {
            res = std::max(res, depth);
        }
        traverse(root->left);
        traverse(root->right);
        depth--; // 即将离开这个节点时进行的操作
    }
};

// 2.分解子问题的求解方法 树的最大深度=max(左子树的最大深度，右子树最大深度)+1
//! 思考点：函数出口，递归函数的定义，递归函数的返回值
class Solution2
{
public:
    int maxDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;

        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        return std::max(leftDepth, rightDepth) + 1;
    }
};

/// 144 二叉树的前序遍历
// 1.遍历的方式
class Solution_1
{
public:
    std::vector<int> res; // 全局量
    std::vector<int> preorderTraversal(TreeNode *root)
    {
        traverse(root);
        return res;
    }

private:
    void traverse(TreeNode *root)
    {
        if (root == nullptr)
            return;
        res.push_back(root->val);
        traverse(root->left);
        traverse(root->right);
    }
};
// 2.分解子问题的求解方法：子问题的结果通过函数返回值返回给父问题
//  函数定义：前序遍历=根+左子树前序遍历+右子树前序遍历
class Solution_2
{
public:
    std::vector<int> preorderTraversal(TreeNode *root)
    {
        std::vector<int> res; // 因为要记录该函数返回结果给到上层所以是局部量
        if (root == nullptr)
            return res;

        res.push_back(root->val);
        std::vector<int> leftResult = preorderTraversal(root->left);
        res.insert(res.end(), leftResult.begin(), leftResult.end());
        std::vector<int> rightResult = preorderTraversal(root->right);
        res.insert(res.end(), rightResult.begin(), rightResult.end());

        return res; // 向上层返回的结果
    }
};

/// 打印每一个节点所在的层数：在遍历过程中就能做到
class GetLevel
{
public:
    void getLevel(TreeNode *root)
    {
        traverse(root, 1);
    }

private:
    void traverse(TreeNode *root, int level)
    {
        if (root == nullptr)
            return;
        printf("Node %d at level %d\n ", root->val, level);
        traverse(root->left, level + 1);
        traverse(root->right, level + 1);
    }
};

// 打印二叉树的左右子树的节点个数
// 思路：遍历过程完成才能知道左右子树的节点个数题目
//*和子树有关，大概率要给函数设置合理的定义和返回值，在后序位置写代码了
class GetNodeNum
{
public:
    int count(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        int leftNum = count(root->left);
        int rightNum = count(root->right);

        printf("Node %p has %d nodes in its left subtree and %d nodes in its right subtree\n", root, leftNum, rightNum);
        return leftNum + rightNum + 1;
    }
};

/// 543 二叉树的最长直径
// 遍历的方法：直径长度=左子树的最大深度+右子树的最大深度
// todo error
// class GetMaxDepth
// {
// public:
//     int depth = 0;
//     int res = 0;

//     int longestPath(TreeNode *root)
//     {
//         if (root == nullptr)
//         {
//             return 0;
//         }
//         if (root->left == nullptr && root->right == nullptr)
//         {
//             return 1;
//         }
//         int le = maxDepth(root->left);
//         int ri = maxDepth(root->right);

//         return le + ri - 1;
//     }
//     int maxDepth(TreeNode *root)
//     {
//         traverse(root);
//         return res;
//     }

// private:
//     void traverse(TreeNode *root)
//     {
//         if (root == nullptr)
//             return;
//         depth++;
//         if (root->left == nullptr && root->right == nullptr)
//         {
//             res = std::max(depth, res);
//         }
//         traverse(root->left);
//         traverse(root->right);
//         depth--;
//     }
// };
// 只有放到后序位置才能做到，因为左右子树都遍历完了才能拿到结果
class GetMaxDepth
{
public:
    int maxDepth = 0;

    int diameterOfBinaryTree(TreeNode *root)
    {
        traverse(root);
        return maxDepth;
    }

private:
    int traverse(TreeNode *root)
    {
        if (root == nullptr)
            return 0;

        int leftMax = traverse(root->left);
        int rightMax = traverse(root->right);

        int cur = leftMax + rightMax;
        maxDepth = std::max(maxDepth, cur);

        return 1 + std::max(leftMax, rightMax); // 返回该节点的最大深度
    }
};

//* 652 寻找重复的子树
/*要找两个结构和数据上完全的树，首先先毙掉随便拿出两个根结点然后挨个遍历其子树看结果的想法。
既然两个树的结构完全一致（包含其数据），那么我们按照某种统一的规则将一棵树的数据取出来然后形成一个序列之类的东西，这个东西也应该一样。
那么这个时候我们再想想：啥玩意在判相等的时候代码少呢？那自然是字符串，省力省时间。
那又怎么证明这个字符串之前出现过呢？哈希表,作为键计数就可，我们也不需要对由树产生出的字符串排序，所以就用unordered_map，省时间
*/
class FindDuplicateSubtrees
{
public:
    std::unordered_map<std::string, int> memo;
    std::vector<TreeNode *> res;

    std::vector<TreeNode *> findDuplicateSubtrees(TreeNode *root)
    {
        traverse(root);
        return res;
    }
    // 函数定义：以root为根的字符串=toString(root->val)+以root->left为根的字符串+以root->right为根的字符串
    std::string traverse(TreeNode *root)
    {
        std::string ss = "";
        if (root == nullptr)
        {
            return "";
        }

        std::string left = traverse(root->left);
        std::string right = traverse(root->right);
        ss = std::to_string(root->val) + " " + left + " " + right;
        memo[ss]++;
        if (memo[ss] == 2)
        {
            res.push_back(root);
        }

        return ss;
    }
};

/// 1373 二叉搜索子树的最大键值和  先从二叉树中找到某节点为根的搜索树(利用中序遍历中产生的子数组如果有序就是它)，然后求和
class MaxSumBST
{
public:
    int maxSum = 0;
    int maxSumBST(TreeNode *root)
    {
        traverse(root);
        return maxSum;
    }

    std::vector<int> traverse(TreeNode *root)
    {
        std::vector<int> vec;
        if (root == nullptr)
        {
            return vec;
        }

        std::vector<int> le = traverse(root->left);
        vec.insert(vec.end(), le.begin(), le.end());
        vec.push_back(root->val);
        std::vector<int> ri = traverse(root->right);
        vec.insert(vec.end(), ri.begin(), ri.end());
        int tmp = 0;
        if (isOrdered(vec, tmp))
        {
            maxSum = std::max(maxSum, tmp);
        }
        return vec;
    }

    bool isOrdered(const std::vector<int> &vec, int &sum)
    { // 如果为真，顺便算下和
        sum = vec[0];
        for (int i = 1; i < vec.size(); i++)
        {
            sum = sum + vec[i];
            if (vec[i - 1] > vec[i])
            {
                return false;
            }
        }
        return true;
    }
};