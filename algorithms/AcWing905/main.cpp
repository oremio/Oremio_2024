// url: https://www.acwing.com/problem/content/907/
// tutorial: https://www.acwing.com/video/335/

/*
每个区间选一个点：
1.将每个区间按右端点从小到大排序
2.从前往后依次枚举每个区间
    如果当前区间中已经包含点，则直接pass
    否则，选择当前区间的右端点
*/
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100010;

int n;
struct Range
{
    int l, r;
    bool operator<(const Range &tmp) const
    {
        return r < tmp.r;
    }
} ran[N];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        ran[i] = {l, r};
    }
    sort(ran, ran + n);

    int cnt = 0, ed = -2e9;
    for (int i = 0; i < n; i++){
        if(ed < ran[i].l) {
            ed = ran[i].r;
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}
