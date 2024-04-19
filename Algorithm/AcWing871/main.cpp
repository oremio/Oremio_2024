// url: https://www.acwing.com/problem/content/873/
// tutorial: https://www.acwing.com/video/296/

/*
约数个数与约数之和：
以12举例，12 = 2^2 * 3^1
注意，这里都是质因子的幂的乘积

12的约数有1， 2， 3， 4， 6， 12
约数个数：（2 + 1） * （1 + 1） = 6，相当于求每个约数的组合个数，前面有三种可能，2^0 = 1, 2^1 = 2 , 2^2 = 4 ,后面有两种可能， 3^0 = 1 , 3^1 = 3 。将前面三种可能和后面两种可能进行排列组合，总共有2 * 3种可能。

约数之和： 相当于对约数个数的每种可能取出，进行相加，得到所有约数的和。
*/

#include <fstream>
#include <iostream>
#include <math.h>
#include <unordered_map>

using namespace std;

typedef long long LL;

const int mod = 1e9 + 7;

int n;
unordered_map<int, int> primes;

int get_divisor_sum(int x)
{
    for (int i = 2; i <= x / i; i++)
    {
        while (x % i == 0)
        {
            x /= i;
            primes[i]++;
        }
    }

    if (x > 1)
        primes[x]++;

    int res = 1;
    for (auto i : primes)
    {
        int sum = 0;
        for (int j = 0; j <= i.second; j++)
            sum += pow(i.first, j);
        res = res * sum;
    }
    return res;
}

int main()
{
    fstream file("input.txt");
    if (file.is_open())
        cin.rdbuf(file.rdbuf());

    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;

        for (int i = 2; i <= x / i; i++)
        {
            while (x % i == 0)
            {
                x /= i;
                primes[i]++;
            }
        }

        if (x > 1)
            primes[x]++;
    }
    LL res = 1;
    for (auto i : primes)
    {
        LL sum = 1;
        // for (int j = 0; j <= i.second; j++)
        //     sum += pow(i.first, j);
        // res = res * sum % mod;

        for (int j = 0; j < i.second; j++)
            sum = (sum * i.first + 1) % mod;

        res = res * sum % mod;
    }
    cout << res << endl;
    return 0;
}
