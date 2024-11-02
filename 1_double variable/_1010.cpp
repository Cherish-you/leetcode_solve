#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// void getNum(int *num) {
//     int count = 0;
//     int i=0;
//     unordered_map<int,int> mp;
//     while(*num!=0) {

//         unordered_map<int,int>::iterator it=mp.find((num[i])%60 ==0)
//         if(it!=mp.end()) {
//             count++;

//         }
//         i++;
//     }
// }
// todo 这时候由于要查找的数很多种可能，time[j]=n*60-time[i],即进行多次查找，不好用
void get(int num[], int n)
{
    int count = 0;
    int cnt[60] = {0};
    for (int i = 0; i < n; i++)
    {

        count = count + cnt[(60 - num[i] % 60) % 60]; // 这样写条件，是在一个有限的范围
        cnt[num[i] % 60]++;                           // 至于这两句话的顺序是因为i<j
    } //! 先更新的话会影响到我的计数
    cout << count << endl;
}

// 暴力法
void getNum(int num[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if ((num[i] + num[j]) % 60 == 0)
            {
                count++;
            }
        }
    }
    cout << count << endl;
}

int main()
{
    string str = "";
    cout << "请输入：" << endl;
    // cin.ignore();
    // cin.clear();
    getline(cin, str);
    int i = 0;
    int num[6 * 10000] = {0};
    int index = 0;
    string temp;           //! 这里写的逻辑就很混乱，用_1_2
    while (i < str.size()) // 字符串中没有'\n'
    {
        if (isdigit(str[i]))
        {
            temp = "";
            temp += str[i];
            i++;
            while (i < str.size() && isdigit(str[i]))
            {
                temp += str[i];
                i++;
            }
            num[index] = stoi(temp);
            index++;
        }
        i++;
    } // 判断边界时c风格的字符串以'\0'（即空格）结束，c++风格字符串使用封装函数，不用管最后一个字符是什么，
    //* getline()中的结束符并没有读入字符串，且结束后结束符会被消耗掉，不放入缓存区

    string tmp = "";
    vector<int> vec;
    for (int j = 0; j < str.length(); ++j)
    {
        if (isdigit(str[j]))
        {
            tmp += str[j];
        }
        if (!isdigit(str[j]) || j == str.length() - 1)
        {
            if (!tmp.empty())
            {
                vec.push_back(stoi(tmp));
                tmp = "";
            }
        }
    }

    getNum(num, index + 1);
    return 0;
}