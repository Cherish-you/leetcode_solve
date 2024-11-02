#include <vector>
#include <stdio.h>
#include <string>
#include <queue>
#include <iostream>
#include <set>

using namespace std;

// 连续空间的数组遍历
void traverse_array(const vector<int> &arr)
{
    for (int i = 0; i < arr.size(); ++i)
    {
    }
}

void traverse_array(const vector<int> &arr, int i)
{
    if (i == arr.size())
        return;

    traverse_array(arr, i + 1);
}
/*----------------------------------------------------------*/
// 逻辑上连续的链表遍历
struct ListNode
{
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

void traverse_list(ListNode *head)
{
    for (ListNode *p = head; p != nullptr; p = p->next)
    {
    }
}

void traverse_list2(ListNode *head)
{
    if (head == nullptr)
        return;
    traverse_list2(head->next);
}
/*------------------------------------------------------*/
// 二叉树不是简单的连续，无法用for来做到遍历，如下遍历框架
//! 二叉树的终止条件几乎都是root==nullptr,只是返回什么的区别
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
struct Node
{
    int val;
    vector<Node *> children;
};

void traverse_binaryTree(TreeNode *root)
{ //! 这一层函数的代码是立足于root的，以root为思考点添加代码，包括前，中，后
    if (root == nullptr)
        return;
    // 前序位置 从root即将进入它的左子树时执行
    traverse_binaryTree(root->left);
    // 中序位置 从左子树回来root，即将进入它的右子树时执行
    traverse_binaryTree(root->right);
    // 后序位置 从它的右子树回来root的时候执行
}

// 二叉树层序遍历
void levelTraverse(TreeNode *root)
{
    if (root == nullptr)
        return;

    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    { // 上到下的遍历
        int sz = q.size();
        for (int i = 0; i < sz; i++)
        { // 左到右的遍历
            TreeNode *cur = q.front();
            q.pop();
            cout << cur->val << " ";
            if (cur->left != nullptr)
                q.push(cur->left);
            if (cur->right != nullptr)
                q.push(cur->right);
        }
    }
}
// todo bfs 解决的问题：在一幅「图」中找到从起点 start 到终点 target 的最近距离
void BFS(Node *start, Node *target)
{
    queue<Node *> q;
    set<Node *> visited; // 避免走回头路

    q.push(start);
    visited.insert(start);

    while (!q.empty())
    {
        int sz = q.size();
        for (int i = 0; i < sz; i++)
        {
            Node *cur = q.front();
            q.pop();
            if (cur->val == target->val)
            {
                return;
            }
            for (Node *child : cur->children)
            {
                if (!visited.count(child))
                {
                    q.push(child);
                    visited.insert(child);
                }
            }
        }
    }
}

/*------------------------------------------------------*/
// 回溯思路
class HuiSu
{
public:
    void traverse(TreeNode *root)
    {
        // 如果节点为空（说明已经越过叶节点），就返回
        if (root == nullptr)
            return;
        // 从节点 root 出发，沿着 left 边走
        printf("从节点 %s 进入节点 %s", root, root->left);
        traverse(root->left);
        // 从节点 root 的左边回来
        printf("从节点 %s 回到节点 %s", root->left, root);

        // 从节点 root 出发，沿着 right 边走
        printf("从节点 %s 进入节点 %s", root, root->right);
        traverse(root->right);
        // 从节点 root 的右边回来
        printf("从节点 %s 回到节点 %s", root->right, root);
    }
    void traverse_multiway(Node *root)
    {
        if (root == nullptr)
            return;
        for (Node *child : root->children)
        {
            printf("从节点 %s 进入节点 %s", root, child);
            traverse_multiway(child);
            printf("从节点 %s 回到节点 %s", child, root);
        }
    }

    //* 回溯遍历思路：着眼点永远是在节点之间移动的过程，类比到二叉树上就是「树枝」
    // void backtrack(...)
    // {
    //     // base case
    //     if (...)
    //         return;

    //     for (int i = 0; i < ...; i++)
    //     {
    //         // 做选择
    //         ...

    //             // 进入下一层决策树
    //             backtrack(...);

    //         // 撤销刚才做的选择
    //         ...
    //     }
    // }
};
/*思考方式
dfs只操作了root,也就是节点
回溯要同时操作root和root->left/root->right,也就是所谓的树枝，因此必须把「做选择」和「撤销选择」的逻辑放在 for 循环里面，否则怎么拿到「树枝」的两个端点
动态规划操作的是子问题，也是子树，利用子解在后序位置求父解
*/

/*------------------------------------------------------*/
//* dfs遍历的思路:它的着眼点永远是在单一的节点上，类比到二叉树上就是处理每个「节点」。
class DFS
{
public:
    void traverse(TreeNode *root)
    {
        if (root == nullptr)
            return;
        // 遍历过的每个节点的值加一
        root->val++;
        traverse(root->left);
        traverse(root->right);
    }

    void traverse_multiway(Node *root)
    {
        if (root == nullptr)
            return;

        // 做选择
        printf("我将要进入节点 %s了\n", to_string(root->val));
        for (Node *child : root->children)
        {

            traverse_multiway(child);
        }
        // 撤销选择
        printf("我将要离开节点 %s了\n", to_string(root->val));
    }
};
