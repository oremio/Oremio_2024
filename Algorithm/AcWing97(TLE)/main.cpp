// url: https://www.acwing.com/problem/content/99/

/*
约数之和，待优化
优化方法：使用快速幂和费马小定理？
*/

#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

typedef long long LL;

const int mod = 9901;

unordered_map<int, int> primes;

// 快速幂
LL quick_pow(LL x, int n, int m) {
    LL res = 1;
    while (n) {
        if (n & 1) res = res * x % m;
        x = x * x % m;
        n >>= 1;
    }
    return res;
}

int main()
{
    fstream file("input.txt");
    if (file.is_open())
        cin.rdbuf(file.rdbuf());

    auto timeStart = clock();
    int a, b;
    cin >> a >> b;

    for (int i = 2; i <= a / i; i++)
    {
        while (a % i == 0)
        {
            a /= i;
            primes[i]++;
        }
    }
    if (a > 1)
        primes[a]++;

    LL res = 1;
    for (auto i : primes)
    {
        LL sum = 1;
        for (int j = 0; j < i.second * b; j++)
            sum = (sum * i.first + 1) % mod;

        res = res * sum % mod;
    }
    cout << res << endl;
    cout << clock() - timeStart << endl;
    return 0;
}
