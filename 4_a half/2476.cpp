#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// #define null -1

// 树中序遍历非递归写法
// void get(int nums[], int size)
// {
//     int p = 0;

//     stack<int> st;

//     // while(nums[2*p+1]!=null||nums[2*p+2]!=null) {
//     //     st.push(p);
//     //     if(nums[]!=null) {
//     //         st.push(rchild);
//     //     }
//     //     if(nums[lchild]!=null) {
//     //         st.push(lchild);
//     //     }
//     // }
//     st.push(p);
//     while (!st.empty())
//     {
//     }
// }

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

TreeNode *createTree(const vector<int> &nums, int index)
{

    if (index >= nums.size() || nums[index] == -1)
    {
        return NULL;
    }
    TreeNode *root = new TreeNode(nums[index]);
    root->left = createTree(nums, 2 * index + 1);
    root->right = createTree(nums, 2 * index + 2);

    return root;
}

void mid(TreeNode *root, vector<int> &vec)
{
    if (root == NULL)
    {
        return;
    }
    mid(root->left, vec);
    vec.push_back(root->val);
    mid(root->right, vec);
}

void closest(TreeNode *root, int queries[], int size)
{
    vector<int> vec;
    mid(root, vec);

    cout << "[";
    for (int i = 0; i < size; i++)
    {
        int left = 0;
        int right = vec.size() - 1;
        while (left <= right)
        {
            int m = left + (right - left) / 2;
            if (vec[m] >= queries[i])
            {
                right = m - 1;
            }
            else
            {
                left = m + 1;
            }
        }

        if (vec[right + 1] == queries[i])
        { // right+1是大于等于它的数
            cout << "[" << vec[right + 1] << "," << vec[right + 1] << "]";
        }
        else if (vec[right + 1] < queries[i])
        {
            cout << "[" << vec[right] << "," << -1 << "]";
        }
        else
        {
            cout << "[" << vec[right] << "," << vec[right + 1] << "]";
        }

        if (i != size - 1)
        {
            cout << ",";
        }
    }
    cout << "]";
}

int main()
{
    vector<int> vec = {6, 2, 13, 1, 4, 9, 15, -1, -1, -1, -1, -1, -1, 14};
    int queries[] = {2, 5, 16};

    TreeNode *root = createTree(vec, 0);

    int size = sizeof(queries) / sizeof(queries[0]);

    closest(root, queries, size);

    return 0;
}