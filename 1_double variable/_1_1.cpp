#include <iostream>
#include <string>
#include <cctype>
#include <vector>

void getTargetSum(const std::vector<int> &vec, int target)
{
    int length = vec.size();
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (vec[i] + vec[j] == target)
            {
                std::cout << "[" << vec[i] << "," << vec[j] << "]" << std::endl;
            }
        }
    }
}
int main()
{
    std::string str = ""; // 以字符串的形式来解析出数字
    std::cout << "enter the nums and the target" << std::endl;
    getline(std::cin, str);
    std::vector<int> vec;
    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]))
        {
            std::string temp = "";
            temp = temp + str[i]; // 直接给字符串只能是常量
            i++;
            while (i < str.length() && isdigit(str[i]))
            {
                temp = temp + str[i];
                i++;
            }
            vec.push_back(std::stoi(temp));
            i--;
        }
    }

    getTargetSum(vec, vec[vec.size() - 1]);
}