#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include <string>
#include <sstream>
//*先找再放，与暴力搜索一致
void getSum(std::vector<int> &nums, int target)
{
    std::unordered_map<int, int> mp;
    for (int i = 0; i < nums.size(); ++i)
    {
        std::unordered_map<int, int>::iterator it = mp.find(target - nums[i]);
        if (it != mp.end())
        {
            std::cout << "[" << it->second << "," << i << "]" << std::endl;
            break;
        }
        mp[nums[i]] = i;
    }
}

int main()
{
    /**
     * 针对输入格式为 nums = [2,7,11,15], target = 9 从这种类型的获取数字
     */
    std::vector<int> results;
    std::string item = "";
    std::cout << "enter the numbers " << '\n';
    std::cin.ignore();
    std::cin.clear();
    std::getline(std::cin, item); // 遇到第三个参数停止读，所以如果不是特别规整的数据，不要用其他的分隔符来读，就用默认换行符
    std::string number = "";
    for (int i = 0; i < item.length(); ++i)
    {
        if (std::isdigit(item[i]))
        {
            number += item[i];
        } //?判断下一个是不是数字是循环干的活，这里已经逻辑完善了，i就只有两种情况,再考虑一下边界
        if (!std::isdigit(item[i]) || i == item.length() - 1)
        {
            if (!number.empty())
            {
                results.push_back(std::stoi(number));
                number = "";
            }
        }
    }
    // for(int i=0;i<item.length();++i) {
    //     if(std::isdigit(item[i])) {
    //         number=number+item[i];
    //     }
    //     if(!std::isdigit(item[i])||i==item.length()-1) {
    //         if(!number.empty()) {
    //             results.push_back(std::stoi(number));
    //             number="";
    //         }
    //     }
    // }

    getSum(results, results.back());
}