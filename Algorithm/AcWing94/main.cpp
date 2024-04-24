// url: https://www.acwing.com/problem/content/96/

/*
递归实现排列型枚举
*/

#include <iostream>

using namespace std;

const int N = 11;

int n;
int tmp[N];
bool st[N];

void dfs (int cnt) {
    if (cnt == n) {
        for (int i = 0; i < n; i++)
            cout << tmp[i] << ' ';
        cout << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!st[i]) {
            st[i] = true;
            tmp[cnt] = i + 1;
            dfs(cnt + 1);
            st[i] = false;
        }
    }
}

int main() {
    cin >> n;
    dfs(0);
    return 0;
}
