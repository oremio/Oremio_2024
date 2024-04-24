// url: https://www.acwing.com/problem/content/94/
// tutorial: https://www.acwing.com/video/110/

/*
递归实现指数型枚举
*/

#include <iostream>

using namespace std;

int n;

void dfs(int cnt, int state) {
    if (cnt == n) {
        for (int i = 0; i < n; i++) {
            if (state >> i & 1)
                cout << i + 1<< ' '; // 注意，从0开始数，因此是i + 1
        }
        cout << endl;
        return;
    }
    // 递归应当执行n次才能到达一个结果
    // 换言之，应当加n次1
    // 故：cnt从0开始数
    dfs(cnt + 1, state);
    dfs(cnt + 1, state | 1 << cnt);

}

int main() {
    cin >> n;
    dfs(0, 0);
    return 0;
}
