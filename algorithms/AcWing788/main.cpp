// url: https://www.acwing.com/problem/content/790/
// tutorial: https://www.acwing.com/video/230/
// TC:

/*
归并排序的基本流程？
1. [L, R] => [L, mid], [mid + 1, R]
2. 递归排序[L, mid]和[mid + 1, R]
3. 归并
应用于本题的求逆序对呢？
3_1. 左右序列经过排序后，双指针依旧是齐头并进
3_2. 这一次的合并过程，需要我们在进行归并的同时计算逆序对
3_3. 如果i指针所指的数严格大于j指针所指，那么这也意味着，i所指的后面所有数（因为此时已排序）也大于j所指
*/

#include <fstream>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 100010;

int n;
int q[N], temp[N];

LL merge_sort(int l, int r)
{
    if (l >= r)
        return 0; // 没有逆序对

    int mid = (l + r) >> 1;
    LL res = merge_sort(l, mid) + merge_sort(mid + 1, r);

    // merge
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
        if (q[i] <= q[j])
            temp[k++] = q[i++];
        else
        {
            temp[k++] = q[j++];
            res += mid - i + 1; // i指针及其之后的数
        }

    // 扫尾
    while(i <= mid)
        temp[k++] = q[i++];
    while(j <= r)
        temp[k++] = q[j++];

    // 物归原主
    for (int i = l, j = 0; i <= r; i++, j++)
        q[i] = temp[j];

    return res;
}

int main()
{
    // ifstream file("input.txt");
    // if (file.is_open())
    // {
    //     cout << "Great!" << endl;
    //     cin.rdbuf(file.rdbuf());
    // }

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> q[i];

    cout << merge_sort(0, n - 1) << endl;

    return 0;
}
