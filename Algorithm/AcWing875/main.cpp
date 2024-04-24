// url: https://www.acwing.com/problem/content/877/
// tutorial: https://www.acwing.com/video/300/

/*
快速幂：
对于a ^ b mod p，需要计算b重循环，对吧？
但是使用快速幂，就能在logb里解决问题
空间换时间，我们需要一些预处理
我们需要获得a ^ (2 ^ 0) mod p, ..., a ^ (2 ^ log2b) mod p的值
其中，每个数是前一个数的平方（显然）
我们可以把2 ^ 0, ..., 2 ^ log2b当成拼图，拼出b（利用二进制知识）
*/
#include <iostream>

using namespace std;

typedef long long LL;

int qmi(int a, int b, int p)
{
    int res = 1 % p;
    while (b)
    {
        if (b & 1)
            res = (LL)res * a % p;
        // 第一次循环：a = a ^ (2 ^ 0)
        // 之后呢？接着往下看↓
        b = b >> 1;
        a = (LL)a * a % p;
    }
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int a, b, p;
        scanf("%d%d%d", &a, &b, &p);
        cout << qmi(a, b, p) << endl;
    }
    return 0;
}
