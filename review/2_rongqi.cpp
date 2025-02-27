#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <list>
#include <stack>

void useVector()
{
    //创建容器
    using std::vector;
    vector<int> v1;
    vector<int> v2(5);
    vector<vector<int>> v3(10,vector<int>());
    vector<int> v4={1,2,3};

    //插删
    v1.capacity();
    v1.reserve(1);//预分配内存
    v1[0]=1;
    v1.push_back(3);
    v1.pop_back();

    v1.insert(v1.begin()+1,3);
    v1.erase(v1.begin()+1);

    //遍历
    for(int i=0;i<v1.size();++i)
    {
        std::cout<<v1[i]<<'\n';
    }
    for(vector<int>::iterator it=v1.begin();it!=v1.end();it++)
    {
        std::cout<<*it<<'\n';
    }
    for(vector<int>::reverse_iterator it=v1.rbegin();it!=v1.rend();it++)
    {
        std::cout<<*it<<'\n';
    }
    for(vector<int>::const_iterator it=v1.cbegin();it!=v1.cend();it++)
    {
        std::cout<<*it<<'\n';
    }
}

void useDeque()
{   
    using std::deque;
    deque<int> dq;
    deque<int> dq_2={1,2,3,4};

    dq.push_back(5);
    dq.pop_back();
    dq.push_front(0);
    dq.pop_front();
    dq.insert(dq.begin()+2,3);
    dq.erase(dq.begin()+2);
    
    int frontNum=dq.front();
    int backNum=dq.back();
    bool isEmpty=dq.empty();

    for(int i=0;i<dq.size();++i)
    {
        std::cout<<dq[i]<<'\n';
    }
    for(deque<int>::iterator it=dq.begin();it!=dq.end();it++)
    {
        std::cout<<*it<<'\n';
    }
    for(deque<int>::reverse_iterator it=dq.rbegin();it!=dq.rend();it++)
    {
        std::cout<<*it<<'\n';
    }
    
//可用作栈，队列等非常灵活的使用首尾的场景
}


void useArray()
{
    using std::array;
    array<int,10> arr;//固定大小，不允许改变
    
}
//上面三个it是随机迭代器，可以支持（即调用）++, --, + n, - n, +=, -=, [], ->
//list,set,map双向迭代器，支持++,--,->
//forward_list是单向迭代器，支持++
//而每一个容器内部都有iterator,reverse_iterator,const_iterator(禁止修改元素),比如在vector中三者就都是随机型，都支持这些
void useList()
{
    using std::list;
    list<int> li;
    list<int>::iterator it=li.begin();
    list<int>::reverse_iterator re_it=li.rbegin();
    list<int>::const_iterator it=li.cbegin();
    
    
}


//非容器，无迭代器
void useStack()
{
    using std::stack;
    stack<int>st;
    stack<int,std::array<int,5>>;
}
int main()
{

}