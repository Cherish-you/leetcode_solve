#include <iostream>
#include <set>
#include <bitset>

// using namespace std;

int main()
{
    std::set<int> s = {1, 2, 3, 4, 5};

    __builtin_popcount(23);//__
    // __lg(s)+1;
    __lg(32);
    __builtin_ctz(23);//据说是gcc的内嵌函数，可移植性差

}