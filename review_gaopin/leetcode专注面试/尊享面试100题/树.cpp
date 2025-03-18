#include <vector>

using namespace std;

/*298.给定root，计算最长连续序列路径的长度
最长连续序列路径：val依次递增1的路径，路径要求是父节点到子节点
思路：分解子问题，以当前节点为终点的最长长度=以当前节点左孩为终点的最长，以当前节点右孩为终点的最长，
*/

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int longestConsecutive(TreeNode *root)
{

    int result = traverse(root, nullptr, 0);
    return result;
}
//前序的实际结果在叶节点处得到，利用前面遍历的节点提供的信息
int traverse(TreeNode *head, TreeNode *parent, int len)
{ //每一个函数的len表示从根节点到当前节点的最长连续长度，实际得到结果是在叶节点处，不过是函数返回时往上更新
    if (head == nullptr)
    { 
        return len;
    }

    if (parent != nullptr && head->val == (parent->val + 1))
        len = len + 1;
    else
        len = 1;

    int leftMaxLen = traverse(head->left, head, len);
    int rightMaxLen = traverse(head->right, head, len);
    return max(max(leftMaxLen, rightMaxLen), len);
}
int res=0;
int tra(TreeNode *head)
{ // 当前节点的长度影响后面节点的长度，所以前序计算
    if (head == nullptr)
    { 
        return 0;
    }

    int leftMaxLen = tra(head->left);
    int rightMaxLen = tra(head->right);
    int Len=1;
    if(head->left!=nullptr && head->val==(head->left->val-1))
    {
        Len=max(Len,leftMaxLen+1);
    }
    if(head->right!=nullptr && head->val==(head->right->val-1))
    {
        Len=max(Len,rightMaxLen+1);
    } 
    res=max(res,Len);    
    return Len;
}

//前序位置的代码根最先执行，后续位置代码最左侧叶子最先执行
//所有建树的逻辑都是递归，递的过程建立节点直到叶子，归的时候确定节点的指向关系
TreeNode *buildTree(vector<int> &vec, int i)
{
    if (i >= vec.size() || vec[i] == -1)
    {
        return nullptr;
    }
    TreeNode *root = new TreeNode(vec[i]);

    root->left = buildTree(vec, 2 * i + 1);
    root->right = buildTree(vec, 2 * i + 2);
}

int main()
{
    vector<int> vec = {1, -1, 3, 2, 4, -1, -1, -1, 5};
    TreeNode *root = buildTree(vec, 0);
    longestConsecutive(root);
}


/*549 也是最长连续序列路径,不同的是可以父到子，也可以是子到父
*/

int ans=0;
pair<int,int> dfs(TreeNode* root)
{
    if(root==nullptr)
    {
        return {0,0};
    }
    auto [leftUp,leftDown]=dfs(root->left);
    auto [rightUp,rightDown]=dfs(root->right);
    int newUp=1;
    int newDown=1;
    if(root->val==root->left->val+1) newUp=max(newUp,leftUp+1);//左侧升序个数+1
    if(root->val==root->left->val-1) newDown=max(newDown,leftDown+1);//左侧降序个数+1
    if(root->val==root->right->val+1) newUp=max(newUp,rightUp+1);//右侧升序个数+1
    if(root->val==root->right->val-1) newDown=max(newDown,rightDown+1);//右侧降序个数+1
    ans=max(ans,newUp+newDown-1);//总个数
    return {newUp,newDown};
}