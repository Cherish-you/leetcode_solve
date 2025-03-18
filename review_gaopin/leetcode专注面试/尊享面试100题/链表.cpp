#include <iostream>

using namespace std;

/*708 向循环链表中插入元素，这里给的head是任意的而不是val最小的节点
所以：先找到值最小的作为头节点，
然后pre，p找到首个大于insertVal的元素，pre->next=Node(insertVal,p);
另外一种情况是所有元素都比他小，这个需要手动设置退出条件*/

class Node
{
public:
    int val;
    Node *next;

    Node() {}

    Node(int _val)
    {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node *_next)
    {
        val = _val;
        next = _next;
    }
};

Node *insert(Node *head, int insertVal)
{ // 因为后面要用到pre,p，所以这里先处理为空和一个节点的情况
    if (head == NULL)
    {
        head = new Node(insertVal);
        head->next = head;
        return head;
    }
    if (head->next == head)
    {
        head->next = new Node(insertVal, head);
        return head;
    }

    Node *pre = head;
    Node *p = head->next;
    Node *realHead = NULL;

    while (pre->val <= p->val)
    {
        pre = p;
        p = p->next;
        if (p == head)
        {
            break;
        } // 注意可能值全部一样，如果不加退出就会死循环
    }
    realHead = p; // p此时就是头节点，pre是尾节点

    while (p->val < insertVal)
    { // 这里采用相同值放左侧，加=就是放右侧
        pre = p;
        p = p->next;
        if (p == realHead)
        { // 说明已经找了一圈，没找到，那就退出,此时pre的后继就是插入的位置，而且恰好和找到的位置相同，不要单独处理
            break;
        }
    }
    pre->next = new Node(insertVal, p);
    return head;
}
