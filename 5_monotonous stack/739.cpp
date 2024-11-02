#include <iostream>
#include <stack>

using namespace std;
// 从右往左

void get(int temperature[], int size, int answer[])
{

    stack<int> st; // 只能存索引，因为要记录的是索引的差值
    for (int i = size - 1; i >= 0; i--)
    {

        while (!st.empty() && temperature[i] >= temperature[st.top()])
        {
            st.pop();
        }
        if (!st.empty())
        {
            answer[i] = st.top() - i;
        }
        st.push(i);
    }
}

// 从左往右
void get2(int temperature[], int size, int *answer)
{
    stack<int> st;
    for (int i = 0; i < size; i++)
    {

        while (!st.empty() && temperature[i] > temperature[st.top()])
        {
            int j = st.top();
            st.pop();
            answer[j] = i - j;
        }
        st.push(i);
    }
}

// 42
// int trap(int height[], int size)
// {
//     int ans = 0;
//     stack<int> st; // 需要用到索引，所以还是存索引而非值
//     st.push(height[0]);
//     for (int i = 1; i < size; i++)
//     {
//         int cur = i;
//         while (i < size && height[i] < height[st.top()])
//         {
//             st.push(i);
//             i++;
//         }
//         if (i < size)
//         {
//             int next = i;
//             int min_height = min(height[cur], height[next]);
//             while (i < size && height[i] < min_height)
//             {
//                 int index = st.top();
//                 st.pop();
//                 ans = ans + min_height - height[index];
//             }
//             st.push(next);
//         }
//     }
//     return ans;
// }//存在逻辑上的错误

int another(int height[], int size)
{
    if (size == 0)
    {
        return 0;
    }
    int ans = 0;

    int leftMax[size];
    leftMax[0] = height[0]; // 左侧没有，自然就是当前高度最大
    for (int i = 1; i < size; ++i)
    {
        leftMax[i] = max(leftMax[i - 1], height[i]); // i位置从左边看的最大高度=max（左侧的最大高度和当前高度）
    }

    int rightMax[size];
    rightMax[size - 1] = height[size - 1]; // 右侧没有，自然就是当前高度最大
    for (int i = size - 2; i >= 0; --i)
    {
        rightMax[i] = max(rightMax[i + 1], height[i]); // i位置从右边看的最大高度=max（右侧的最大高度和当前高度）
    }

    for (int i = 0; i < size; ++i)
    {
        ans += min(leftMax[i], rightMax[i]) - height[i]; // 左右最大高度的最小值-当前高度=i位置能接的水
    }

    return ans;
}

int trap(int height[], int size)
{
    int ans = 0;

    stack<int> st; // 栈的有序性是自己维护出来的，在加入栈前把栈里所有小于他的都弹出去了
//维护一个顶向下的单调递增
    for (int i = 0; i < size; ++i)
    {

        while (!st.empty() && height[i] > st.top())
        {
            int bottom = st.top();
            st.pop();
            if (st.empty())
                break;
            int left = st.top();
            int width = min(height[left], height[i]) - height[bottom];
            int length = i - left - 1;
            ans = ans + width * length;
        }
        st.push(i);
    }
    return ans;
}


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
// 单调递减栈模板
int monotoneIncreasingStack(int nums[], int size)
{
    stack<int> st;

    for (int i = 0; i < size; ++i)
    {
        while (!st.empty() && nums[i] <= nums[st.top()])
        {
            st.pop();
        }
        st.push(i);
    }
}

int main()
{
    int height[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int size = sizeof(height) / sizeof(height[0]);
    cout << trap(height, size) << endl;
}