#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// 一种思路：并查集 + 枚举删除每个点的情况
// 另一种思路：邻接表 + 枚举删除每个点的情况 + 深搜计算dp？

// dp是一种最大值，我们要求dp的最小值

const int N = 1010;

typedef pair<int, int> PII;

int n;
int p[N], cnt[N];
vector<PII> input;

void init(int ex) {
    memset(cnt, 0, sizeof cnt);

    for (int i = 1; i <= n; i++)
        if (i != ex)
            p[i] = i;
        else
            p[i] = 0;
    return;
}

int find(int x) {
    if (x != p[x])
        p[x] = find(p[x]);
    return p[x];
}

void merge(int a, int b) {
    p[find(b)] = find(a);
}

int main() {
    ifstream file("input.txt");
    if (file.is_open())
        cin.rdbuf(file.rdbuf());

    cin >> n;

    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        input.emplace_back(a, b);
    }

    int res_dp = 1010;
    vector<int> res;

    for (int i = 1; i <= n; i++) {
        // 枚举删除每个点的情况
        init(i);
        for (auto pii : input)
            if (pii.first != i && pii.second != i)
                merge(pii.first, pii.second);
        // 然后统计连通城市群中的最大值dp
        for (int j = 1; j <= n; j++)
            cnt[p[j]]++;

        int dp = -1;
        for (int j = 1; j <= n; j++)
            if (cnt[j] > dp)
                dp = cnt[j];

        if (dp < res_dp) {
            res_dp = dp;
            res.clear();
            res.push_back(i);
        } else if (dp == res_dp)
            res.push_back(i);
        else
            ;
    }

    

    for (auto i : res)
        cout << i << ' ';

    return 0;
}
