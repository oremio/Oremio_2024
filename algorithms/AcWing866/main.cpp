// url: https://www.acwing.com/problem/content/868/
// tutorial: https://www.acwing.com/video/291/

/*
试除法：
如果有d | n（注意，整除符号的前面是较小的那个数）
则有 n/d | n（也就是，可以整除的约数往往成双成对）
从而有 d^2 <= n

想一想，判断条件怎么写？
不推荐写法其一：i ^ 2 <= n
原因：可能溢出
不推荐写法其二：i <= sqrt(n)
原因：慢
推荐写法：i <= x / i
*/

#include <iostream>

using namespace std;

bool is_prime(int x)
{
    if (x < 2)
        return false;
    else
    {
        for (int i = 2; i <= x / i; i++)
            if (x % i == 0)
                return false;
        return true;
    }
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        cout << (is_prime(x) ? "Yes" : "No") << endl;
    }
    return 0;
}
