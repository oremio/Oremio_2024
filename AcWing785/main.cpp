#include <iostream>

using namespace std;

const int N = 100010;

int q[N];

void quickSort(int q[], int l, int r)
{
    if (l >= r)
        return; //不要忘记了！！既然是递归，一开始就得有返回条件

    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j)
    {
        while (q[++i] < x)
            ;
        while (q[--j] > x)
            ;
        if (i < j) // 不要忘记了！……忘记了会怎么样呢？
            swap(q[i], q[j]);
    }
    quickSort(q, l, j);
    quickSort(q, j + 1, r);
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &q[i]);
    quickSort(q, 0, n - 1);
    for (int i = 0; i < n; i++)
        printf("%d ", q[i]);
    return 0;
}