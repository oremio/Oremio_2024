// url: https://www.acwing.com/problem/content/95/
// tutorial: https://www.acwing.com/video/111/

/*
递归实现组合型枚举
排列和组合感觉是分别代表两类递归？→不好说
但可以明确的是，组合的递归树是一个二叉树，要么选，要么不选，我们利用二进制状态state来表示已选的元素
而排列则是多叉树，且分支逐层递减，
从左到右遍历每个分支的动力由一个for循环提供，
而从上到下则是依靠递归。
*/

#include <iostream>

using namespace std;

int n, m;

void dfs(int idx, int cnt, int state) { // idx：数到几了；cnt：选了几个；state：二进制数表示选择状态
    if (cnt + n - idx < m) // n - idx：剩余可选的数
        return;
    if (cnt == m) { // 选完了
        for (int i = 0; i < n; i++) {
            if (state >> i & 1)
                cout << i + 1 << ' ';
        }
        cout << endl;
        return;
    }
    dfs(idx + 1, cnt + 1, state | (1 << idx));
    dfs(idx + 1, cnt, state);
}

int main() {
    cin >> n >> m;
    dfs(0, 0, 0);
    return 0;
}
