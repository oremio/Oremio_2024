// url: https://www.acwing.com/problem/content/788/
// tutorial: https://www.acwing.com/video/228/
// TC(time complexity): n

/*
1. 找到分界点x, q[L], q[(L + r) / 2], q[R]
2. 左边所有数 <= x, 右边所有数 >= x
3_1. k <= 左边的数的个数: 递归左边
3_2. k >= 左边的数的个数: 递归右边
*/

#include <fstream>
#include <iostream>

using namespace std;

const int N = 100010;

int n, k;
int q[N];

int quick_sort(int l, int r, int k)
{
    if (l == r)
        return q[l]; // 永远保证第k小的数在区间[l, r]里，因此l == r可以之间返回
    int x = q[l], i = l - 1, j = r + 1;
    while (i < j)
    {
        while (q[++i] < x)
            ;
        while (q[--j] > x)
            ;
        if (i < j)
            swap(q[i], q[j]);
    }
    int SL = j - l + 1;
    if (k <= SL)
        return quick_sort(l, j, k);
    return quick_sort(j + 1, r, k - SL);
}

int main()
{
    ifstream file("input.txt");
    if (file.is_open())
        cin.rdbuf(file.rdbuf());

    cin >> n >> k;

    for (int i = 0; i < n; i++)
        cin >> q[i];

    cout << quick_sort(0, n - 1, k);

    return 0;
}
