// url : https://www.nowcoder.com/practice/f8538f9ae3f1484fb137789dec6eedb9

#include <unordered_set>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1010;

unordered_set<int> primes;
bool st[N];

void get_primes(int n) {
    if (n < 2) return;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) { // get
            primes.insert(i);
            if (i <= n / i) {
                int tmp = i << 1;
                while (tmp <= n) {
                    st[tmp] = true;
                    tmp += i;
                }
            }
        }
    }
}

int find_prime(int n) {
    int res = 1010, mini = 1010;
    for (const auto prime : primes) {
        if(primes.find(n - prime) != primes.end() && abs(n - 2 * prime) < res) {
            res = abs(n - 2 * prime);
            mini = prime;
        }
    }
    return mini;
}

int main() {
    int n;
    cin >> n;
    get_primes(n);
    int m1 = find_prime(n);
    int m2 = n - m1;
    if (m1 > m2)
        swap(m1, m2);
    cout << m1 << m2 << endl;
    return 0;
}
