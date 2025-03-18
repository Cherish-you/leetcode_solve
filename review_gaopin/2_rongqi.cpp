#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <list>
#include <set>
#include <unordered_set>
#include <string>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>

void useVector()
{
    // 创建容器
    using std::vector;
    vector<int> v1;
    vector<int> v2(5);
    vector<vector<int>> v3(10, vector<int>());
    vector<int> v4 = {1, 2, 3};

    // 插删
    v1.capacity();
    v1.reserve(1); // 预分配内存
    v1[0] = 1;
    v1.push_back(3);
    v1.pop_back();

    int front = v1.front();
    int back = v1.back();

    v1.insert(v1.begin() + 1, 3);
    v1.erase(v1.begin() + 1);

    // 遍历
    for (int i = 0; i < v1.size(); ++i)
    {
        std::cout << v1[i] << '\n';
    }
    for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
    {
        std::cout << *it << '\n';
    }
    for (vector<int>::reverse_iterator it = v1.rbegin(); it != v1.rend(); it++)
    {
        std::cout << *it << '\n';
    }
    for (vector<int>::const_iterator it = v1.cbegin(); it != v1.cend(); it++)
    {
        std::cout << *it << '\n';
    }
}

/*两者对比：
vector：元素连续存于内存。超容量时重新分配大的连续空间，复制元素并释放旧空间。
deque：由多个固定大小连续存储块构成，块内元素连续，块间不一定连续，靠中控器管理。
随机访问都是o(1),但vector更高；vector适合频繁随机访问、少头部操作场景，deque适合头尾高效插入删除场景
*/
void useDeque()
{
    using std::deque;
    deque<int> dq;
    deque<int> dq_2 = {1, 2, 3, 4};

    dq.push_back(5);
    dq.pop_back();
    dq.push_front(0);
    dq.pop_front();
    dq.insert(dq.begin() + 2, 3);
    dq.erase(dq.begin() + 2);

    int frontNum = dq.front();
    int backNum = dq.back();
    bool isEmpty = dq.empty();

    for (int i = 0; i < dq.size(); ++i)
    {
        std::cout << dq[i] << '\n';
    }
    for (deque<int>::iterator it = dq.begin(); it != dq.end(); it++)
    {
        std::cout << *it << '\n';
    }
    for (deque<int>::reverse_iterator it = dq.rbegin(); it != dq.rend(); it++)
    {
        std::cout << *it << '\n';
    }

    // 可用作栈，队列等非常灵活的使用首尾的场景
}

void useArray()
{
    using std::array;
    array<int, 10> arr; // 固定大小，不允许改变
}
// 上面三个it是随机迭代器，可以支持（即调用）++, --, + n, - n, +=, -=, [], ->
// list,set,map双向迭代器，支持++,--,->
// forward_list是单向迭代器，支持++
// 而每一个容器内部都有iterator,reverse_iterator,const_iterator(禁止修改指向的元素，即只读),比如在vector中三者就都是随机型，都支持这些
void useList()
{
    using std::list;
    list<int> li;                     // 空容器
    list<int> li_3(5);                // 5个元素,默认值是0
    list<int> li_4(5, 10);            // 5个元素，值为10
    list<int> li_2 = {4, 5, 6, 7, 8}; // 初始化列表

    list<int>::iterator it = li.begin();
    list<int>::reverse_iterator re_it = li.rbegin();
    list<int>::const_iterator it = li.cbegin();

    li_2.push_back(9);
    li_2.pop_back();
    li_2.push_front(3);
    li_2.pop_front();
    li_2.insert(li_2.cbegin(), 1);
    li_2.erase(li.cbegin());

    int size = li_2.size();
    bool isEmpty = li_2.empty();
    li_2.reverse();                     // o(N),逆序整个链表
    li_2.merge(li_4);                   // o(n) 这个要求要合并的两个是有序的，然后最后结果存在调用该函数的对象里
    li_2.splice(li_2.cbegin()++, li_3); // o(1) 左++返回的未加之前的值，所以还是首个位置，然后拼接li_3
    li_2.unique();                      // 去除重复的元素  o(n)
    li_2.sort();                        // 非std的sort,是成员函数，效率要更高

    // 遍历
    for (list<int>::iterator it = li_2.begin(); it != li_2.end(); it++)
    {
        std::cout << *it << '\n';
    }

    /*高频插入删除：如实时任务调度队列
    大型对象存储：避免vector扩容时的拷贝开销
    需要稳定迭代器：如游戏中的动态实体管理
    特殊操作需求：需要splice/merge等链表专属操作
    */
}

void useSet()
{
    using std::set;
    set<int> s;                         // 升序
    set<int, std::greater<int>> s_desc; // 降序
    set<int> s_2 = {3, 4, 5, 8, 7};

    // 基本函数，红黑树的内在，均为o(log n)
    s.insert(10); // 参数为值
    s.insert(20);
    s.erase(10); // 参数为值
    if (s.count(20))
    { // 元素只允许出现一次，所以count可以判断元素是否存在,或者下面的方法
        auto pos = s.find(20);
        if (pos != s.end())
        {
            s.erase(pos); // 参数为位置
        }
    }

    // 范围查询,当然了，只有在multiset中才有意义
    set<int>::iterator it = s_2.lower_bound(5);   // 返回第一个>=5的位置
    set<int>::iterator it_2 = s_2.upper_bound(5); // 返回第一个>5的位置
    set<int>::iterator tmp = --it_2;
    int number_of_5 = std::distance(it, tmp); // 可以得到5的数量

    // 遍历
    for (set<int>::const_iterator cit = s_2.cbegin(); cit != s_2.cend(); cit++)
    {
        std::cout << *cit << '\n';
    }

    /*使用场景：
    有序且唯一元素的场景（如排行榜、字典序存储）
    范围查询​（如查找区间内的元素）
    */

    using std::multiset;
    /*和上面唯一的区别就是有序但元素不唯一，场景如成绩统计*/

    using std::unordered_set;
    /*hash的内在，无序但元素唯一，效率都是o(1),需要快速查找某个值但不关心顺序，如缓存*/
}

void useMap()
{
    using std::map;

    map<std::string, int> mp;
    map<std::string, int, std::greater<std::string>> mp_2;     // std::string是支持><的，比较参照字符的ascil码，从左往右比
    map<std::string, int> mp_3 = {{"alice", 14}, {"bob", 16}}; // 初始化列表

    // 基本函数，红黑树的内在，均为o(log n)
    mp.insert(std::make_pair("weiyang", 18));
    mp.insert({"weimian", 20});
    mp.erase("weimian"); // 参数为键

    int size = mp.size();
    bool isEmpty = mp.empty();

    // 范围查询，当然了，只有在multimap中才有意义，因为允许重复键
    map<std::string, int>::iterator it = mp.lower_bound("weiyang");   // 返回第一个>=参数键的位置
    map<std::string, int>::iterator it_2 = mp.upper_bound("weiyang"); // 返回第一个>参数键的位置
    std::advance(it_2, -1);                                           // 将传入的迭代器做常数项的移动
    int number_of_5 = std::distance(it, it_2);                        // 可以得到容器中这个键对应元素的数量

    // 查找
    map<std::string, int>::iterator pos = mp.find("weiyang");
    if (pos != mp.end())
    {
        mp.erase(pos); // 参数为位置
    }

    // 遍历
    for (map<std::string, int>::reverse_iterator rit = mp.rbegin(); rit != mp.rend(); rit++)
    {
        std::cout << rit->first << " " << rit->second << '\n';
    }

    /*
    虽然支持下标，但不建议使用下标访问
    场景：需按键有序遍历、键唯一（如字典、统计排序结果），且需要记录映射关系。
    ​缺点：插入/查找较哈希表慢，适合数据量较小或需要顺序访问的场景。
    */

    using std::multimap;
    /*
    场景：允许重复键且需有序（如学生ID对应多个成绩）且需要记录映射关系
    */
    using std::unordered_map;

    /*
    场景：高频查找、无需排序，且需要保持映射关系
    */
}

// 非容器，无迭代器
void useStack()
{
    // o(1)
    using std::stack;
    stack<int> st;
    stack<int, std::vector<int>> st_2; // 传入的容器要支持push_back(),pop_back(),back(),如vector,deque,list

    // 基础函数
    st.push(5);
    st.pop();
    int size = st.size();
    bool isEmpty = st.empty();
    int top = st.top();

    // 单调，
    // 或者：就是元素寻找满足条件的第一个相邻元素，找到了就退出
    // 1进栈，7比1大，1找到了退出，7进栈，然后是4，4不满足，4继续进栈...
    int arr[6] = {1, 7, 4, 5, 3, 2};
    for (int i = 0; i < 6; ++i)
    {
        while (!st.empty() && arr[i] >= arr[st.top()])
        {
            st.pop();
        } // 把栈里所有比你小的清出去
        st.push(i);
    }

    for (int i = 0; i < 6; ++i)
    {
        while (!st.empty() && arr[i] <= arr[st.top()])
        {
            st.pop();
        }
        st.push(i);
    }
}

void useQueue()
{
    // o(1)
    using std::queue;
    queue<int> qu;
    queue<int, std::list<int>> qu_2; // 要支持push_back(),pop_front(),back(),front(),如deque,list

    qu.push(3);
    qu.pop();
    qu.empty();
    qu.size();
    qu.front();
    qu.back();

    // o(log n) 是由于要通过堆化维护一个最值
    using std::priority_queue; // 所以只需要支持push_back(),pop_back(),front()即可，如vector(效率是最高的，因为频繁的随机访问)，deque,list
    priority_queue<int, std::vector<int>, std::greater_equal<int>> pri_qu;
    pri_qu.push(3); // 从尾部进来，然后向上调整
    pri_qu.pop();   // 将顶部和尾部交换位置，然后从尾部出去，顶部向下调整
    int maxElement = pri_qu.top();
    pri_qu.size();
    pri_qu.empty();
}

int main()
{
}