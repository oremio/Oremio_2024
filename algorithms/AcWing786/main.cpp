#include <iostream>

using namespace std;

const int N = 100010;
int n, k;
int q[N];

int quickSort(int l, int r, int k)
{
    if (l == r)
        return q[l]; // 返回第k个数
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
    int leftLength = j - l + 1;
    if (k <= leftLength)
        return quickSort(l, j, k);
    else
        return quickSort(j + 1, r, k - leftLength);
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> q[i];
    }
    cout << quickSort(0, n - 1, k) << endl;
    return 0;
}