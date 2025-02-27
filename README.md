种种数据结构，皆为**数组**（顺序存储）和**链表**（链式存储）的变换。

数据结构的关键点在于**遍历和访问**，即增删查改等基本操作。

种种算法，皆为**穷举**。穷举的关键点在于**无遗漏和无冗余**。熟练掌握算法框架，可以做到无遗漏；充分利用信息，可以做到无冗余。



各种结构的遍历(遇见算法题如果没有思路，先把遍历列出来，再添加细节)：

```
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

//后面要涉及到递归，说明：
函数内部局部变量只在当前函数使用，即值不能传递；能传递的地方：函数引用传，返回值传
前序位置的代码只能从函数参数中获取父节点传递来的数据。
中序位置的代码不仅可以获取参数数据，还可以获取到左子树通过函数返回值传递回来的数据。
后序位置的代码最强，不仅可以获取参数数据，还可以同时获取到左右子树通过函数返回值传递回来的数据。

//二叉树的遍历
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
void traverse_binaryTree(TreeNode * root)
{//这一层函数的代码是立足于root的，以root为思考点添加代码，包括前，中，后三个时间点
	if(root==nullptr)
		return;
	traverse_binaryTree(root->left);
	traverse_binaryTree(root->right);
}
void level_binaryTree(TreeNode * root)
{
	if(root==nullptr)
		return;
	queue<TreeNode *>qu;
	qu.push(root);
	
	while(!qu.empty())
	{
		for(int i=0;i<qu.size();++i)
		{
			TreeNode cur=qu.front();
			qu.pop();
			if(cur->left!=nullptr)
			{
				qu.push(cur->left);
			}
			if(cur->right!=nullptr)
				qu.push(cur->right);
		}
	}
}

//多叉树的遍历：
struct Node 
{
	int val;
	std::vector<Node *>children;
};
void traverse_multi(Node * root)
{
	if(root==nullptr)
		return;
	for(int i=0;i<root->children.size();++i)
	{
		traverse_multi(root->children[i]);
	}
}
void level_multi(Node * root)
{
	if(root==nullptr)
		return;
	queue<Node *> qu;
	qu.push(root);
	while(!qu.empty())
	{
		for(int i=0;i<qu.size();++i)
		{
			Node * cur=qu.front();
			qu.pop();
			cout<<cur->val<<" "
			for(int i=0;i<cur->children.size();++i)
			{
				if(cur->children[i]!=nullptr)
					qu.push(cur->children[i]);
			}
		}
		cout<<stdl;
	}
}

//图的遍历（先思考多叉树）：
class Graph
{
private:
	vector<Node *> point;
public:
	void traverse_map(const Graph &g)
	{
		unordered_set<Node *> visited;
		vector<Node *>path;
		for(int i=0;i<point.size();++i)
		{//非联通才这样，要不只执行一遍就行了
			traverse(g.point[i],visited,path);
		}
	}
	void traverse(Node *root,unordered_set<Node *> visited,vector<Node *>&path)
	{	
		if(root==nullptr||visited.count(root))
			return;
		path.push_back(root);
		visited.emplace(root);
		for(int i=0;i<root->children.size();++i)
		{
			traverse(root->children[i],visited);
		}
    }
    
    void level_map(Graph& g,Node *root，vector<Node *>&path)
    {
    	if(root==nullptr)
			return;
		queue<Node *> qu;
		qu.push(root);
		while(!qu.empty())
		{
			for(int i=0;i<qu.size();++i)
			{
				Node * cur=qu.front();
				qu.pop();
				path.emplace(cur);
				for(int i=0;i<cur->children.size();++i)
				{
					if(cur->children[i]!=nullptr)
						qu.push(cur->children[i]);
				}
			}
			cout<<stdl;
		}
    }
};

```



```
//这是cacc的刷题处：

//3.考虑策略，任务必须相邻，优先给后面人：只要把数组切成几个连续子数组，均下来在保证时间最小同时前面的人小？
void getAttribute(int arr[],int length,pair<int,int> person[],int personNum)
{	
	int totalSum=0;
	for(int i=0;i<length;++i)
	{
		totalSum+=arr[i];
	}
	int targetSum=totalSum/personNum;
	int remainder=totalSum%personNum;
	
	for(int i=0;i<)
}

//4
void getMaxAnd(int arr[],int length,int le,int ri)
{
	int maxAnd=INT_MIN;
	for(int i=le;i<ri;++i)
	{
		for(int j=i+1;j<=ri;++j)
		{
			maxAnd=max(maxAnd,arr[i]&arr[j]);
		}
	}
    return maxAnd;
}
void update(int arr[],int length,int le,int ri,int val)
{
	for(int i=le-1;i<ri;++i)
	{
		arr[i]+=val;
	}
}


```



```
//没有提示，纯手写，这是leetcode的刷题处：

//对框架不够熟悉：
auto window = //元素出现次数ymap<int,int>;窗口的元素和一个int变量
int left=0;int right=0;
int ans;
while(right<nums.size())
{
	windows.add(nums[right]);
	right++;
	
	//因扩大窗口而导致结果的更新
	
	while(windows needs shrink)
	{
		windows.remove(nums[left]);
		left++;
		
		//因缩小窗口而导致结果的更新
	}
	
	//这里保留的是满足要求的窗口
	ans+=;//right-left+1 以right为右区间的子区间个数;nums.size()-right 以left为左区间right+x为右区间的子区间个数
}
/*----------------------------------*/



```

they are some solutions of leetcode 

now it have 
leetcode 刷题注意事项：

常用容器：

vector,数组的特性，可动态扩容（拷贝+分配新空间），但有消耗

```c++
vector<int> vec;

// 插入和删除
vec.push_back(x);         // O(1)，尾部插入
vec.pop_back();           // O(1)，移除尾部
vec.insert(pos, x);       // O(n)，在指定位置插入
vec.erase(pos);           // O(n)，移除指定位置元素
vec.clear();              // O(n)，清空容器

// 访问元素
int x = vec[i];           // O(1)，按索引访问
int front = vec.front();  // O(1)，获取首元素
int back = vec.back();    // O(1)，获取尾元素

// 属性和操作
size_t size = vec.size(); // O(1)，获取元素数量
bool empty = vec.empty(); // O(1)，检查是否为空
vec.reserve(n);           // O(n)，预留容量
vec.resize(n, val);       // O(n)，调整大小，填充为 val

// 排序
sort(vec.begin(), vec.end());  // O(n log n)，升序排序
binary_search(vec.begin(),vec.end(),target); //o(log n)
reverse(vec.begin(), vec.end()); // O(n)，反转元素

//优化：预留足够的空间避免扩容；移动语义减少拷贝；二分替代线性搜索

```

list,

stack,queue,

```
stack<int> st;//递归模拟，括号匹配，逆序

// 插入/删除
st.push(x);               // O(1)，压栈
st.pop();                 // O(1)，弹栈

// 访问
int top = st.top();       // O(1)，访问栈顶元素

// 属性
bool isEmpty = st.empty(); // O(1)，是否为空
size_t size = st.size();  // O(1)，元素数量

//括号匹配，入栈半边，遇右半边出栈，最后看栈空情况
for (char c : s) {
    if (c == '(' || c == '{' || c == '[') {
        st.push(c); // 左括号入栈
    } else {
        if (st.empty()) return false;
        char top = st.top();
        st.pop();
        if ((c == ')' && top != '(') ||
            (c == '}' && top != '{') ||
            (c == ']' && top != '[')) {
            return false;
        }
    }
}

queue<int> q;
// 插入/删除
q.push(x);                // O(1)，尾部插入
q.pop();                  // O(1)，头部删除

// 访问
int front = q.front();    // O(1)，访问队首
int back = q.back();      // O(1)，访问队尾

// 属性
bool isEmpty = q.empty(); // O(1)，是否为空
size_t size = q.size();   // O(1)，元素数量
```

priority_queue（持续维护添加元素的最值）

```
less<type>()    //从小到大排序 <
grater<type>()  //从大到小排序 >
less_equal<type>()  //  <=
gtater_equal<type>()//  >=

// 最大堆（默认）
priority_queue<int> maxHeap;

// 最小堆
priority_queue<int, vector<int>, greater<int>> minHeap;

// 插入
maxHeap.push(x);          // O(log n)，插入元素
minHeap.push(x);          // O(log n)，插入元素

// 访问堆顶
int top = maxHeap.top();  // O(1)，返回堆顶元素
int minTop = minHeap.top(); 

// 删除堆顶
maxHeap.pop();            // O(log n)，删除堆顶元素

```

deque（其实一侧就能完成单调，即单调栈，给另一侧是为了拿两个最值）

```c++
deque<int> dq;

// 插入和删除
dq.push_back(x);          // O(1)，尾部插入
dq.push_front(x);         // O(1)，头部插入
dq.pop_back();            // O(1)，移除尾部
dq.pop_front();           // O(1)，移除头部

// 访问
int front = dq.front();   // O(1)，访问头部
int back = dq.back();     // O(1)，访问尾部
int val = dq[i];          // O(1)，按索引访问

// 属性和操作
size_t size = dq.size();  // O(1)，获取元素数量
bool empty = dq.empty();  // O(1)，检查是否为空
dq.clear();               // O(n)，清空容器


//维持单调，由尾部->首部 单增 能拿到两个最值

deque<int> dq;
    for (int i = 0; i < nums.size(); ++i) {
        while (!dq.empty() && nums[dq.back()] <= nums[i]) 			              dq.pop_back(); // 保持单调
        dq.push_back(i);

    }
  
```



set,map(排序o(logn),不能重复键)；unordered_set/map(无序o(1)，不能重复键) multiset/map(排序o(logn)，可重复键)

```
//创建
set<int> s;
map<int,int> mp;

// 插入和删除维持有序但遍历会上升到o(n)
s.insert(x);              // O(log n)，插入元素
s.erase(x);               // O(log n)，删除元素
mp[key]=value;
mp.erase(key);

// 查找,用特定位置推效率最高，然后是下面的函数，最后是遍历，end指向最后元素的后一个
s.begin(),s.end(),s.rbegin(),s.rend()

auto it = s.find(x);      // O(log n)，查找首个x，返回迭代器类型
bool exists = s.count(x); // O(log n)，判断 x 是否存在

// 范围查询
auto lower = s.lower_bound(x); // O(log n)，第一个 >= x 的元素
auto upper = s.upper_bound(x); // O(log n)，第一个 > x 的元素

// 属性和操作
size_t size = s.size();   // O(1)，获取元素数量
s.clear();                // O(n)，清空集合

//set 动态第k小:*(s.begin()+k-1)
//map 频率统计，键值关系


```







 0_guide
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

​	while (window needs shrink) {
​    	// 缩小窗口
​    	window.removeFirst(nums[left]);
​    	left++;
​	}
​	//进行窗口内数据的更新

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

