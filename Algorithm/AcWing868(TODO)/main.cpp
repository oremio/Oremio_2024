// url: https://www.acwing.com/problem/content/870/
// tutorial: https://www.acwing.com/video/293/

/*
筛质数：
埃拉托斯特尼筛法（埃氏筛法）和线性筛法都是用于筛选质数的经典算法，它们在实现方式和时间复杂度上有所不同。

埃拉托斯特尼筛法（埃氏筛法）
原理：
初始化一个标记数组，标记每个数是否为质数。
从 2 开始遍历到 sqrt(n)，将每个质数的倍数标记为合数。
时间复杂度：O(nloglogn)

线性筛法
核心：只用每个合数的最小质因子筛选出这个合数
原理：
初始化一个标记数组，标记每个数是否为质数。
从小到大遍历每个数，用当前的数去乘以已经找到的质数，并标记每个合数。
时间复杂度：O(n)

相同点：
两种方法都可以用于筛选质数，都能有效地找到一定范围内的所有质数。
不同点：
埃拉托斯特尼筛法的时间复杂度为O(nloglogn)，相对较慢，但是实现简单，适用于较小的范围。
线性筛法的时间复杂度为O(n)，相对较快，但是实现略微复杂，需要额外的空间来保存已经找到的质数。适用于较大的范围。
*/

#include <iostream>

using namespace std;

const int N = 1000010;

int n;
int cnt, prime[N];
bool st[N];

int Eratosthenes_get_prime(int x)
{
    if (x < 2)
        return 0;
    else
    {
        int res = 0;
        for (int i = 2; i <= x; i++)
            if (!st[i])
            {
                res++;
                // 第一处优化：以下的内容，从这个if域里拿出去也可以，但我们选择放进来，也就是，只用质数的倍数筛合数
                if (i <= x / i) // 第二处优化：去掉内层的这个if判定也可以，但我们选择放进来，也就是，只用小于sqrt(x)的质数的倍数筛合数
                {
                    int tmp = 2 * i;
                    while (tmp <= x)
                    {
                        st[tmp] = true;
                        tmp += i;
                    }
                }
            }
        return res;
    }
}

int linear_get_prime(int x)
{
}

int main()
{
    cin >> n;
    cout << linear_get_prime(n) << endl;
    return 0;
}
