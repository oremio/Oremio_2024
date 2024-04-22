// url: https://www.acwing.com/problem/content/802/
// tutorial: https://www.acwing.com/video/252/

/*
尝试双指针的思路：
1.先写一遍暴力的做法
2.观察两层循环中的单调性

具体到本题：数组元素的目标和
i从左往右扫描A数组时，值不断增大
j则在i的驱动下，从右往左，值不断减小
这就是单调性
*/
#include <fstream>
#include <iostream>

using namespace std;

const int N = 100010;

int n, m, x;
int a[N], b[N];

int main()
{
    ifstream file("input.txt");
    if (file.is_open())
        cin.rdbuf(file.rdbuf());

    cin >> n >> m >> x;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];

    for (int i = 0, j = m - 1; i < n; i++)
    {
        while (j >= 0 && a[i] + b[j] >= x)
        {
            if (a[i] + b[j] == x)
            {
                cout << i << ' ' << j;
                break;
            }
            j--;
        }
        if (a[i] + b[j] == x)
            break;
    }
    return 0;
}
