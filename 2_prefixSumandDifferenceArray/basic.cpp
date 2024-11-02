#include <iostream>
#include <vector>

// 对于二阶的计算就是完全类比一阶的来

// prefix sum 前缀和  比原数组要大1，因为进行了索引偏移
// 一维：
class PrefixSum
{
private:
    int *prefix; //* 既然是数组，方便使用自然保留它的大小
    int size;

public:
    PrefixSum() = delete; // 禁止无参构造

    PrefixSum(int arr[], int n)
    { //* 构造前缀和数组
        this->size = n + 1;
        prefix = new int[size];
        prefix[0] = 0; // 偏移一位，为避免出现-1的索引
        for (int i = 1; i < n + 1; ++i)
        {
            prefix[i] = prefix[i - 1] + arr[i - 1];
        }
    }

    //* 使用前缀和数组计算区间和，由于是成员函数，所以不需要再给原数组
    int getNum(int start, int end)
    {
        int res = prefix[end + 1] - prefix[start]; // 用数轴理解，左边不动
        return res;
    }

    int *getPrefix()
    { //! 这样传出去外面的指针是不知道具体的堆区长度的，解决方案为用容器(因为会自动管理大小)或同时传出长度
        return prefix;
    }
    void printPrefix()
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << prefix[i] << " ";
        }
    }

    ~PrefixSum()
    {
        delete[] prefix;
    }
};

// 二维：
class PrefixSum2D
{
private:
    //* 拥有一个类的对象必须要在该类的构造函数执行之前用:对该对象进行构造(基本类型和容器可推迟到构造函数中)
    //* 说明：在类中写的是没有分配内存的，在实例对象时才分配
    std::vector<std::vector<int>> prefix;

    /*
    一阶可以这样写，但是实操发现二阶指针是用来传堆下开辟的二维数组的，一般的二阶数组在不指定列情况下是传不进来的,即直接传数组名进不来，int **arr, int hang, int lie
    重申：二维数组就不要用指针，太容易出错，直接用vector<vector<int>>
    参数应该这样写：vector<vector<int>> vec*/
public:
    PrefixSum2D(const std::vector<std::vector<int>> &arr) //// 因为是以指针传的数组，所以同时给上行，列参数，
    {
        // int row = arr.size() + 1;
        // int column = arr[0].size() + 1;
        // prefix = new int *[row];
        // for (int i = 0; i < row; ++i)
        // {
        //     prefix[i] = new int[column];
        // }
        // //* 开始构造前缀和数组
        // for (int i = 0; i < row; ++i)
        // {
        //     prefix[i][0] = 0;
        // }
        // for (int j = 0; j < column; ++j)
        // {
        //     prefix[0][j] = 0;
        // }

        int row = arr.size() + 1;
        int column = arr[0].size() + 1;
        prefix = std::vector<std::vector<int>>(row, std::vector<int>(column, 0));

        for (int i = 1; i < row; ++i)
        {
            for (int j = 1; j < column; ++j)
            {
                prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + arr[i - 1][j - 1];
            }
        }
    }

    int getMatrixNum(int x_1, int y_1, int x_2, int y_2)
    {
        // 用固定（0，0）点，做矩形理解
        int res = prefix[x_2 + 1][y_2 + 1] - prefix[x_1][y_2 + 1] - prefix[x_2 + 1][y_1] + prefix[x_1][y_1];
        return res;
    }

    void printPre()
    {
        int row = prefix.size();
        int column = prefix[0].size();
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                std::cout << prefix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    PrefixSum2D() = delete;
};

void testPrefixSum()
{
    int arr[6] = {3, 5, 2, -2, 4, 1};
    PrefixSum pre(arr, 6);
    pre.printPrefix();
    std::cout << pre.getNum(1, 4) << std::endl; // 测试正确

    std::vector<std::vector<int>> arr2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    PrefixSum2D pre2(arr2);
    pre2.printPre();
    std::cout << pre2.getMatrixNum(1, 1, 2, 2) << std::endl;
}

// difference array 差分 是和原数组一样大的数组，没有进行索引偏移
// 一维
class DifferenceArray
{
private:
    std::vector<int> diff;

public:
    DifferenceArray(std::vector<int> &nums) : diff(nums.size(), 0)
    { // 构造差分数组  同时索引越界的另一种处理，判断，前面是靠偏移
        for (int i = 0; i < nums.size(); ++i)
        {
            diff[i] = nums[i];
            if (i > 0)
            {
                diff[i] = diff[i] - nums[i - 1];
            }
        }
    }

    // [i,j]区间加val的操作等价于差分数组diff[i] += val, diff[j+1] -= val
    void update(int i, int j, int val)
    {
        diff[i] += val;
        if (j + 1 < diff.size())
        { // 防止越界
            diff[j + 1] -= val;
        }
    }

    // 恢复数组
    void restore(std::vector<int> &original)
    {
        for (int i = 0; i < diff.size(); ++i)
        {
            original[i] = diff[i];
            if (i > 0)
            {
                original[i] += original[i - 1];
            }
        }
    }

    void print()
    {
        for (auto &i : diff)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

// 二维：
class DifferenceArray2D
{
private:
    std::vector<std::vector<int>> diff;

public:
    DifferenceArray2D(const std::vector<std::vector<int>> &original) : diff(original.size(), std::vector<int>(original[0].size(), 0))
    {
        for (int i = 0; i < original.size(); i++)
        {
            for (int j = 0; j < original[0].size(); j++)
            {
                diff[i][j] = original[i][j];
                if (i > 0)
                    diff[i][j] = diff[i][j] - original[i - 1][j];
                if (j > 0)
                    diff[i][j] = diff[i][j] - original[i][j - 1];
                if (i > 0 && j > 0)
                    diff[i][j] = diff[i][j] + original[i - 1][j - 1];
            }
        }
    }

    //(x_1,y_1) to (x_2,y_2)的值增加val等价于(x_1,y_1)增加val，(x_2+1,y_1)减少val，(x_1,y_2+1)减少val，(x_2+1,y_2+1)增加val
    void update(int x_1, int y_1, int x_2, int y_2, int val)
    {
        diff[x_1][y_1] += val;
        int row = diff.size();
        int col = diff[0].size();
        if (x_2 + 1 < row)
            diff[x_2 + 1][y_1] -= val;
        if (y_2 + 1 < col)
            diff[x_1][y_2 + 1] -= val;
        if ((x_2 + 1 < row) && (y_2 + 1 < col))
            diff[x_2 + 1][y_2 + 1] += val;
    }

    void restore(std::vector<std::vector<int>> &original)
    {
        for (int i = 0; i < diff.size(); i++)
        {
            for (int j = 0; j < diff[0].size(); j++)
            {
                original[i][j] = diff[i][j];
                if (i > 0)
                    original[i][j] += original[i - 1][j];
                if (j > 0)
                    original[i][j] += original[i][j - 1];
                if (i > 0 && j > 0)
                    original[i][j] -= original[i - 1][j - 1];
            }
        }
    }
    void print()
    {
        for (int i = 0; i < diff.size(); i++)
        {
            for (int j = 0; j < diff[0].size(); j++)
            {
                std::cout << diff[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

void testDifferenceArray()
{
    std::vector<int> arr = {3, 5, 2, -2, 4, 1};
    DifferenceArray di(arr);
    di.print();
    di.update(2, 4, 5); //[2,4]内 加5
    di.print();
    std::vector<int> res(arr.size(), 0);
    di.restore(res);
    for (int i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << " ";
    }
    std::cout << std::endl; // 测试一维 结果成功

    std::vector<std::vector<int>> arr2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DifferenceArray2D di_2(arr2);
    di_2.print();
    di_2.update(1, 1, 2, 2, 5);
    di_2.print();
    std::vector<std::vector<int>> ans(arr2.size(), std::vector<int>(arr2[0].size(), 0));
    di_2.restore(ans);
    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[0].size(); j++)
        {
            std::cout << ans[i][j] << " ";
        }
        std::cout << std::endl; // 测试二维，结果成功
    }
}

int main()
{
    testPrefixSum();
    std::cout << "-------------------------------" << std::endl;
    testDifferenceArray();
    return 0;
}