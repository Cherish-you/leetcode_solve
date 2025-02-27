// 常见读入举例：

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Instance
{
    int i;
    int j;
    int k;
    Instance() {}
    Instance(int i, int j, int k) : i(i), j(j), k(k) {}
};

int main()
{
    /*1.cin以空格、Tab键和换行符作为输入的分隔符，
    getline()会读取整行内容，包括空格字符，直到遇到换行符（即第三个参数）为止
    while((ch=getchar())!='\n') 读取一个任意字符，用于逐字符处理
    */

    // 2. 一行字符串读取并解析
    int N;
    string str_N = "";
    cin >> N;
    to_string(N); // int到string
    cin.ignore(); // 清除缓冲区，这里用作忽略上一次输入后的换行符，避免getline出问题
    string line;
    cout << "请输入一行带空格的字符串: ";
    getline(cin, line);
    istringstream iss(line);
    vector<int> parsed_numbers; // 不知道数量,通过push_back
    string tmp = "";
    while (getline(iss, tmp, ','))
    {
        parsed_numbers.push_back(stoi(tmp)); // string到int
    }

    // 3.构造对象，然后加入容器
    int i, j, k;
    cin >> i >> j >> k;
    vector<Instance> vec(2); // 知道数量，通过索引
    for (int index = 0; index < 2; index++)
    {
        // Instance tmp = Instance(i, j, k);
        // vec[index] = move(tmp);//也可行，报错的原因是写有参构造函数的同时需要显式提供默认构造函数
        // vec[index] = Instance(i, j, k); // 可行，这个对象本来就是右值，不用移动语义
    }
}