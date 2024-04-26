#include <iostream>
#include <map>
#include <fstream>
using namespace std;

// 暴力 + 前缀和
// 进阶：双指针 + 前缀和

// 一个规律：i~j是最长时间段，则下一个最长时间段必然以j以后的下标为起点（好像不对）

const int N = 110;

int minlost, n;
int num[N], pre[N];

int main() {
    ifstream file("input.txt");
    if (file.is_open())
        cin.rdbuf(file.rdbuf());

    cin >> minlost;
    while (cin >> num[n++]);
    n--;
    if (!n) return 0;

    pre[0] = num[0];
    for (int i = 1; i < n; i++)
        pre[i] = pre[i - 1] + num[i];

    map<int, int> res;

    // n == 1, todo?

    int maxlen = -1;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int len = j - i + 1;
            if (minlost * len <= pre[j] - pre[i] + num[i]) {
                if (len > maxlen) {
                    res.clear();
                    maxlen = len;
                    res[i] = j;
                }
                else if (len == maxlen) {
                    res[i] = j;
                }
                else;
            }
        }
    }

    for (auto i : res) {
        cout << i.first << '-' << i.second << ' ';
    }
}
