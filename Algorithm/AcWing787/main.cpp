// url: https://www.acwing.com/problem/content/789/
// tutorial: https://www.acwing.com/video/229/
// TC: nlogn

/*
0. 确定分界点: mid = (l + r) / 2
1. 递归排序left、right
2. 归并(难点)：合二为一
    如何归并？
    - 双指针在两个序列共同前进，依次比较
    两个值相同时选哪个序列？
    - 一般选同一个序列，这样可以保证递归排序的稳定性
*/

#include <fstream>
#include <iostream>

using namespace std;

const int N = 1000010;

int n;
int q[N], temp[N];

void merge_sort(int q[], int l, int r)
{
    if (l >= r)
        return;

    int mid = (l + r) >> 1;

    merge_sort(q, l, mid), merge_sort(q, mid + 1, r);

    int k = 0, i = l, j = mid + 1; // k表示已经合并了几个数, i&j就是两个指针
    while (i <= mid && j <= r)
    {
        if (q[i] <= q[j])
            temp[k++] = q[i++];
        else
            temp[k++] = q[j++];
    }
    while (i <= mid)
        temp[k++] = q[i++];
    while (j <= r)
        temp[k++] = q[j++];
    for (i = l, j = 0; i <= r; i++, j++)
        q[i] = temp[j];
}

int main()
{
    // ifstream file("input.txt");
    // if (file.is_open())
    // {
    //     cin.rdbuf(file.rdbuf());
    // }

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> q[i];

    merge_sort(q, 0, n - 1);

    for (int i = 0; i < n; i++)
        cout << q[i] << ' ';

    return 0;
}
