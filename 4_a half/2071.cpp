#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int get(vector<int> &tasks, vector<int> &workers, int pills, int strength)
{
    sort(tasks.begin(), tasks.end());
    sort(workers.begin(), workers.end());
    int si = workers.size();
    int ti = tasks.size();
    //! 每次调用check时，tasks,workers,pills,strength都是不变的,变的只有mid
    auto check = [&](int mid) -> bool
    {
        int p = pills;
        int j = si - 1;
        deque<int> dq; // 始终用的是一个队列而不是一次循环一个队列
        for (int i = mid - 1; i >= 0; i--)
        { // 从大到小枚举所有任务

            while (j >= si - mid && workers[j] + strength >= tasks[i])
            {                              // 从最大的工人开始找所有加上strength大于等于该任务的workers,只取任务数个，
                                           // 这里没有区分是吃药大于还是本来就大于，总之它是可以完成该任务的，就把工人的值加进去
                dq.push_front(workers[j]); // 统一从前端入，这样后端就是最大值，前端就是最小值
                j--;
            }
            if (dq.size() == 0)
            {
                return false;
            }
            else if (dq.back() >= tasks[i]) // 这里开始区分是吃药还是本来就大于
            {
                dq.pop_back();
            }
            else
            {
                if (!p)
                {
                    return false;
                }
                else
                {
                    p--;
                    dq.pop_front();
                }
            }
        }
        return true;
    };

    int left = 1;
    // int right=workers.size();//这里工人数未必大于任务数
    int right = min(si, ti);
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (check(mid))
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return left - 1;
}

int main()
{
    vector<int> tasks = {5, 4};
    vector<int> workers = {0, 0, 0};
    int pills = 1;
    int strength = 5;
    cout << get(tasks, workers, pills, strength) << endl;
    return 0;
}