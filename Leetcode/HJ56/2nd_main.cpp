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
