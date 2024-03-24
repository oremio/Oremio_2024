#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Rec
{
    int x, y;
    bool operator<(const Rec &t) const
    {
        return x < t.x || x == t.x && y < t.y;
    }
} e[5];

bool cmp(Rec a, Rec b) // 返回值含义：a是否应该排在b的前面
{
    return a.x > b.x;
}

int main()
{
    vector<int> a{1, 2, 3, 4, 5};
    reverse(a.begin(), a.end());

    int b[] = {1, 2, 3, 4, 5};
    reverse(b, b + 6); // 左闭右开

    int d[] = {1, 1, 2, 2, 3, 3, 4};
    int m = unique(d, d + 7) - d;

    vector<int> c({1, 1, 2, 2, 3, 3, 4});
    c.erase(unique(c.begin(), c.end()), c.end()); // unique()返回一个新的尾迭代器，erase()将原来的尾迭代器与新的尾迭代器之间的空间释放

    srand(time(0));
    random_shuffle(a.begin(), a.end());

    sort(a.begin(), a.end());
    sort(a.begin(), a.end(), greater<int>());

    for (int i = 0; i < 5; i++)
    {
        e[i].x = -i;
        e[i].y = i;
    }
    sort(e, e + 5);

    int *p = lower_bound(b, b + 5, 3);
    int t = upper_bound(b, b + 5, 4) - b;
}
