// url: https://www.acwing.com/problem/content/787/
// tutorial: https://www.acwing.com/video/227/
// TC(time complexity): nlogn

/*
1.确定分界点: q[1], q[(l+r)/2], q[r], random
2.调整区间(难点): 小于等于x放左边，大于等于x放右边
3.递归处理左右两端
*/

#include <fstream>
#include <iostream>

using namespace std;

const int N = 1e6 + 10;

int n;
int q[N];

void quick_sort(int q[], int l, int r)
{
    if (l >= r)
        return;
    int x = q[l], i = l - 1, j = r + 1;
    while (i < j)
    {
        while (q[++i] < x);
        while (q[--j] > x);
        if (i < j)
            swap(q[i], q[j]);
    } // 跳出while后，i在最后一个小于x的数的右边，j在第一个大于x的数的左边
    quick_sort(q, l, j); // 这里如果右边选i，那就是i - 1
    quick_sort(q, j + 1, r);  // ↑那么这里就是i，但如果按照上面的x = q[l]，就会产生边界问题。j与x = q[r]同理。
}

int main()
{
    ifstream file("input.txt");
    if (file.is_open())
    {
        // cout << "Yes" << endl;
        cin.rdbuf(file.rdbuf());
    }

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> q[i];

    quick_sort(q, 0, n - 1);

    for (int i = 0; i < n; i++)
        cout << q[i] << ' ';
    cout << endl;

    return 0;
}
