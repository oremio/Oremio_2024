// url: https://www.acwing.com/problem/content/797/
// tutorial: acwing.com/video/238/
// TC: n

/*
1.核心算法：
s[i] = s[i - 1] + ai
2.前缀和数组的作用？
数组中任意一段的和都可以轻易计算，计算公式是s[r] - s[l - 1]
3.需要一个S0用于处理边界
例如，求[1, 10]区间的和时，就是S10 - S0
*/

#include <iostream>

using namespace std;

const int N = 100010;

int a[N], s[N];

int main(){
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        int x;
        cin >> x;
        a[i] = x;
        s[i] = s[i - 1] + a[i];
    }
    while(m--){
        int l, r;
        cin >> l >> r;
        cout << s[r] - s[l - 1] << endl;
    }
    return 0;
}
