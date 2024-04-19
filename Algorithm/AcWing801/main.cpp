// url: https://www.acwing.com/problem/content/803/
// tutorial: https://www.acwing.com/video/246/

/*
先介绍一下位运算的常用操作：
1. 把第k位（注意，个位是第0位）移到最后一位：n >> k
2. 取出最后1位：n & 1

本题怎么做呢？
我们要实现一个函数lowbit()，它能得到一个二进制数，只含所给的整数的二进制表示中的最后一位1（其他位均为0）
我们将这个整数循环减去lowbit提取出来的数，做了几次减法就是有几个1

如何实现lowbit()呢？
回忆一下，补码 = 逐位取反，末尾加1
平时做组原题的时候，求一个数的相反数的补码，
其实就是从最后一位1开始，包括这个1的后面位数全部不变，前面位数全部取反
所以x & -x就是lowbit()！
*/
#include <iostream>

using namespace std;

int n;

int lowbit(int x)
{
    return x & -x;
}

int main()
{
    cin >> n;
    while (n--)
    {
        int x, cnt = 0;
        cin >> x;
        while (x)
        {
            x -= lowbit(x);
            cnt++;
        }
        cout << cnt << ' ';
    }
    cout << endl;
    return 0;
}
