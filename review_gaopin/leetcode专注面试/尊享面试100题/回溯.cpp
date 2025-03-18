#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>


using namespace std;

/*1087 花括号展开*/
// vector<vector<int>> getString(string s)
// {
//     vector<vector<int>> result;
//     vector<int> current;
    
//     unordered_map<int,vector<int>> choice;
//     int leftPos=-1;
//     int rightPos=-1;
//     for(int i=0;i<s.length();++i)
//     {
//         if(s[i]=='{')
//         {
//             s[i]='*';//提供一个占位符
//             leftPos=i;
//         }
//         else if(s[i]=='}')
//         {
//             rightPos=i;
//             string tmp=s.substr(leftPos+1,rightPos-leftPos-1);
//             istringstream iss(tmp);
//             while(iss>>)
//         }
//     }
//     traverse(s,result,current)
// }

// void traverse(string s,vector<vector<int>>&result,vector<int>&current)
// {
//     if(current.size()==s.size())
//     {

//     }
//     for(int i=0;i<s.size();++i)
//     {

//     }
// }


vector<string> expand(string s)
{
    vector<string> res,curr;
    string str="";
    res.push_back(str);

    for(int i=0;i<s.length();++i)
    {//发现了遍历处理字符串的特点：我只关心当前i前面的元素，后面的元素是后面循环要考虑的
        if(s[i]=='{'&&str!="")
        {//i={,说明前面一定出现了唯一的元素，已经存在了curr
            curr.push_back(str);
            append(res,curr);
            str="";
            curr.clear();
            continue;
        }
        else if(s[i]=='}')
        {//说明前面一定出现了可选的元素，且已经存在了curr里
            curr.push_back(str);
            append(res,curr);
            str="";        
            curr.clear();
            continue;
        }
        else if(s[i]!='{')
        {
            if(s[i]==',')
            {//可选的元素
                curr.push_back(str);
                str="";
            }
            else
            {//唯一的元素
                str.push_back(s[i]);
            }
        }
    }
    curr.push_back(str);
    append(res,curr);
    return res;
}

void append(vector<string>&res,vector<string>&curr)
{
    vector<string> tmp;
    string s = "";
    sort(curr.begin(), curr.end(), [](const auto& a, const auto& b){    // 排序，为了保持字典序。
        return a < b;
    });
    for(int i = 0; i < res.size(); i++){
        for(int j = 0; j < curr.size(); j++){
            s = res[i];
            tmp.push_back(s.append(curr[j]));
        }
    }
    res = tmp;
}

int main()
{

}