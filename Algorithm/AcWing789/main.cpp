// url: https://www.acwing.com/problem/content/791/
// tutorial: https://www.acwing.com/video/231/

/*
（整数）二分的本质是什么？
    - 并不是单调性
    - 可以找到这样一种性质，将整个区间一分为二
    - 二分可以帮助我们找到「满足这一性质」以及「不满足这一性质」的「边界」
（整数）二分的步骤？
    我们定义「满足这一性质」= 左，如何找到左的边界？
    mid = (l + r + 1) >> 2
    if(check(mid)) // 检查左不左
        [l, r] => [mid, r] // 左了！那么左的边界在右（也包括mid自身）
    else
        [l, r] => [l ,mid - 1] // 不左！那么左的边界在更左
    我们定义「不满足这一性质」= 右，如何找到右的边界？
    mid = (l + r) >> 2
    if(check(mid)) // 检查右不右
        [l, r] => [l, mid] // 右了！那么右的边界在左（也包括mid自身）
    else
        [l, r] => [mid + 1, r] // 不右！那么边界在更右
    Elon Musk直呼内行。
*/

#include <fstream>
#include <iostream>

using namespace std;

const int N = 100010;

int n, m;
int q[N];

int main()
{
    // ifstream file("input.txt");
    // if (file.is_open())
    // {
    //     cin.rdbuf(file.rdbuf());
    // }

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> q[i];
    while (m--)
    {
        int x;
        cin >> x;

        int l = 0, r = n - 1;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            if (q[mid] >= x) // 找到满足这一性质的（左）边界
                r = mid;
            else
                l = mid + 1;
        } // 退出while时，l和r相等
        if (q[l] != x)
            cout << "-1 -1" << endl;
        else
        {
            cout << l << ' ';

            int l = 0, r = n - 1;

            while (l < r)
            {
                int mid = (l + r + 1) >> 1;
                if (q[mid] <= x) // 找到满足这一性质的（右）边界
                    l = mid;
                else
                    r = mid - 1;
            }
            cout << r << endl;
        }
    }
    return 0;
}
