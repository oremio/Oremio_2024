// url: https://www.nowcoder.com/practice/1221ec77125d4370833fd3ad5ba72395

#include <iostream>
using namespace std;

const int N = 32;

int month[N];

int main() {
    int n;
    cin >> n;
    month[1] = 1;
    if (n == 1 || n == 2) { cout << 1 << endl; return 0; }
    month[2] = 0;

    int sum = month[1];
    for (int i = 3; i <= n; i++) {
        month[i] = sum;
        sum += month[i - 1];
    }
    // 这里显然还可以简化空间，因为我们只用到了三个数
    // 但是懒得想了

    sum = sum + month[n - 1] + month[n - 2];
    cout << sum << endl;
    return 0;
}
