// url: https://www.nowcoder.com/practice/7299c12e6abb437c87ad3e712383ff84

/*
本题做法：利用约数之和的公式求完全数

约数之和：
以12举例，12 = 2^2 * 3^1
注意，这里都是质因子的幂的乘积

12的约数之和 = (2^0 + 2^1 + 2^2) * (3^0 + 3^1)
将上式展开，就是六个约数相加，对吧？
*/

#include <iostream>
#include <math.h>
#include <unordered_map>
using namespace std;

unordered_map<int, int> primes;

int get_divisor_sum(int x)
{
    int self = x;
    primes.clear();

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
    return res - self;
}

int main() {
    int n, cnt = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        if(i == get_divisor_sum(i)) cnt++;
    }
    cout << cnt << endl;
    return 0;
}
