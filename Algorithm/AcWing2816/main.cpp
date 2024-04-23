// url: https://www.acwing.com/problem/content/2818/
// tutorial: https://www.acwing.com/video/1942/

/*
判断a序列是否为b序列的子序列（子序列→可以不连续）
做法：贪心 + 双指针
*/

#include <iostream>

using namespace std;

const int N = 100010;

int n, m;
int a[N], b[N];

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] == b[j])
            i++;
        j++;
    }
    if (i == n && j <= m)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}
