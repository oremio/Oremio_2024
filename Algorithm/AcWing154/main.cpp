#include <iostream>

using namespace std;

const int N = 1000010; // 10^6

int n, k;
int a[N]; // 一个注意点：我们存储的是下标
int q[N];

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int hh = 0, tt = -1;
    for (int i = 0; i < n; i++)
    {
        // 判断是否滑出了窗口
        if (hh <= tt && i - k + 1 > q[hh])
            hh++;

        while (hh <= tt && a[i] <= a[q[tt]])
            // 我们需要越右的，性质越好的（在此处即为越小）
            tt--; // 可见，单调队列并不是严格的队列，因为可以队尾弹出元素
        q[++tt] = i;

        if (i >= k - 1)
            cout << a[q[hh]] << ' ';

    }
    cout << endl;
    hh = 0, tt = -1;
    for (int i = 0; i < n; i++)
    {
        // 判断是否滑出了窗口
        if (hh <= tt && i - k + 1 > q[hh])
            hh++;

        while (hh <= tt && a[i] >= a[q[tt]])
            tt--;
        q[++tt] = i;
        
        if (i >= k - 1)
            cout << a[q[hh]] << ' ';
    }
    return 0;
}
