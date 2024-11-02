/*遍历可以走过每一个节点（其实也可以是树枝），更改一下可以走过每一个缝隙（相邻节点之间）；
函数内部的代码都是相较节点root的；
后序位置可以获取到子函数的结果；
树的递归终止条件是一样的
单独抽出一个节点，就是根节点，它需要做什么事情？需要在什么时候（前/中/后序位置）做，其他的节点不用你操心，递归函数会帮你在所有节点上执行相同的操作
*/

#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// 226 翻转二叉树
// 思路：遍历模板,然后前序位置操作本个函数的节点即可

class FlipBinaryTree
{
public:
    TreeNode *flipTree(TreeNode *root)
    {
        traverse(root);
        return root;
    }

private:
    void traverse(TreeNode *root)
    {
        if (root == nullptr)
            return;

        TreeNode *tmp = root->left;
        root->left = root->right;
        root->right = tmp;

        traverse(root->left);
        traverse(root->right);
    }
};
// 定义：一棵树的翻转=交换（左子树的翻转，右子树的翻转）返回值应为根节点
class FlipBinaryTree2
{
public:
    TreeNode *flipTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        TreeNode *left = flipTree(root->left);
        TreeNode *right = flipTree(root->right);

        TreeNode *tmp = root->left;
        root->left = root->right;
        root->right = tmp;

        return root;
    }
};

// 116 填充每个二叉树节点的右侧指针，需要的是相邻的节点，一般的遍历只能找到同一个父节点的相邻
// 这时候要遍历的是空而不是节点，就变成了三叉树
struct Node
{
    int val;
    Node *left;
    Node *right;
    Node *next;
};
class ConnectRightNode
{
public:
    Node *connect(Node *root)
    {
        traverse(root->left, root->right);
        return root;
    }

private:
    void traverse(Node *node1, Node *node2)
    {
        if (node1 == nullptr || node2 == nullptr)
            return;

        node1->next = node2;

        traverse(node1->left, node1->right);
        traverse(node1->right, node2->left);
        traverse(node2->left, node2->right);
    }
};
// 填充父节点的和填充子节点没什么关系，无法分解子问题

// 114 将二叉树展开成链表 完全自己想的，非常棒！！！
/*思路：先序是根左右，与先序相同的顺序，
将二叉树展开成链表=根节点+将左子树展开成链表+将右子树展开成链表
*/
class FlattenBinaryTree
{
public:
    TreeNode *flatten(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        TreeNode *leftList = flatten(root->left);
        TreeNode *rightList = flatten(root->right);

        // 这里已经完成了左右子树的链表化
        root->left = nullptr;
        root->right = leftList;
        // 从root开始找，root能执行到这里就不为空，因为不能确定leftList是否为空
        TreeNode *tmp = root;
        while (tmp->right != nullptr)
            tmp = tmp->right;
        tmp->right = rightList;

        return root;
    }
};

// 654 最大二叉树
// 思路：建树=建立根节点+建左子树+建右子树
class MaxBinaryTree
{
public:
    TreeNode *build(const vector<int> &nums)
    {
        return constructMaximumBinaryTree(nums, 0, nums.size() - 1);
    }
    TreeNode *constructMaximumBinaryTree(const vector<int> &nums, int start, int end)
    {
        if (start > end)
            return nullptr;

        // 索引比值可获得信息量更多
        int maxIndex = findMax(nums);
        TreeNode *root = new TreeNode(nums[maxIndex]);

        root->left = constructMaximumBinaryTree(nums, start, maxIndex - 1);
        root->right = constructMaximumBinaryTree(nums, maxIndex + 1, end);

        return root;
    }

private:
    int findMax(const vector<int> &nums)
    {
        int maxIndex = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > nums[maxIndex])
                maxIndex = i;
        }
        return maxIndex;
    }
};

// 105 从前序与中序遍历序列构造二叉树 建树=根节点+左子树+右子树
class BuildTree
{
public:
    TreeNode *buildTree(vector<int> &preorder, int preStart, int preEnd, vector<int> &inorder, int inStart, int inEnd)
    {
        if (preStart > preEnd)
            return nullptr;

        int rootVal = preorder[preStart];
        int tarIndex = findIndex(inorder, preorder[preStart]); // 也等于小于它索引的元素个数
        int leftSize = tarIndex - inStart;                     // 左子树大小

        TreeNode *root = new TreeNode(rootVal);
        root->left = buildTree(preorder, preStart + 1, preStart + leftSize, inorder, inStart, tarIndex - 1);
        root->right = buildTree(preorder, preStart + leftSize + 1, preEnd, inorder, tarIndex + 1, inEnd);

        return root;
    }

private:
    int findIndex(const vector<int> &nums, int target)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == target)
                return i;
        }
        return -1;
    }
};

// 106 从中序与后序遍历序列构造二叉树
class BuildBinaryTree
{
public:
    TreeNode *buildTree(vector<int> &inorder, int inStart, int inEnd, vector<int> &postorder, int postStart, int postEnd)
    {
        if (postStart > postEnd)
            return nullptr;

        int rootVal = postorder[postEnd];
        int tarIndex = findIndex(inorder, rootVal);
        int leftSize = tarIndex - inStart;

        TreeNode *root = new TreeNode(rootVal);
        root->left = buildTree(inorder, inStart, tarIndex - 1, postorder, postStart, postStart + leftSize - 1);
        root->right = buildTree(inorder, tarIndex + 1, inEnd, postorder, postStart + leftSize, postEnd - 1);
    }

private:
    int findIndex(const vector<int> &nums, int target)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == target)
                return i;
        }
        return -1;
    }
};
