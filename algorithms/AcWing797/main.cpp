// url: https://www.acwing.com/problem/content/799/
// tutorial: https://www.acwing.com/video/242/

/*
差分是前缀和的逆运算
换言之，差分数组的前缀和就是原数组

差分数组的功能：
能使原数组在任意区间加上一个数

原理：
假设原数组为a[N]，差分数组为b[N]
要在原数组的l ~ r加上一个数c
考虑到原数组是差分数组的前缀和
因此只需要让差分数组的b[l] += c，可使后面所有数的前缀和都多一个c
再让差分数组的b[r + 1] -= c，可使后面所有数的不该多出来的c抵消掉
这就是差分数组的insert操作，我们亦可以用此操作来构造差分数组
例如，a[1] = 1，可视为在1 ~ 1加上一个数c = 1
*/
#include <iostream>
#include <fstream>

using namespace std;

const int N = 100010;

int n, m;
int diff[N]; // 甚至不需要原数组（也就是前缀和数组）

void insert(int l, int r, int x) {
    diff[l] += x;
    diff[r + 1] -= x;
}

int main() {
    ifstream file("input.txt");
    if (file.is_open())
        cin.rdbuf(file.rdbuf());

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        insert(i, i, x);
    }
    for (int i = 1; i <= m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        insert(l, r, x);
    }
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += diff[i];
        cout << sum << ' ';
    }
    return 0;
}
