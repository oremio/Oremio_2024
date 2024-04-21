// url: https://www.acwing.com/problem/content/908/
// tutorial: https://www.acwing.com/video/336/

/*
区间分组：
1.将所有区间按左端点从小到大排序
2.从前往后处理每个区间，判断能否将其放到某个现有的组中
    2-1.如果不存在这样的组，则开新组，然后再将其放进去
    2-2.如果存在这样的组，将其放进去，并更新当前组的max_r

如果按右端点排序，反例：
[1, 3], [2, 5], [4, 100], [10, 13]
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
        return l < tmp.l;
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

