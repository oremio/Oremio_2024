// url: https://www.acwing.com/problem/content/874/
// tutorial: https://www.acwing.com/video/297/

/*
欧几里得算法（辗转相除法）求最大公约数

前置知识：d | x, d | y，有d | ax + by
欧几里得算法的原理：gcd(a, b) = gcd(b , a mod b)
证明：
a mod b = a - c * b（c就是 a / b）
根据前置知识可知，gcd(a, b) = gcd(b , a - c * b)
因此，gcd(a, b) = gcd(b , a mod b)

注：gcd = greatest common divisor
*/
#include <iostream>

using namespace std;

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        cout << gcd(a, b) << endl;
    }
    return 0;
}
