#include <algorithm>
#include <bitset>
#include <ctime>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main()
{
    vector<int> a[233];

    struct Rec
    {
        int x, y;
        bool operator<(const Rec &t) const
        {
            return x > t.x;
        }
    };
    vector<Rec> b;
    b.size();
    b.empty();

    vector<int> c({1, 2, 3});

    cout << c.front() << ' ' << c[0] << *c.begin() << endl;
    cout << c.back() << ' ' << c[c.size() - 1] << endl;

    c.push_back(4);
    c.pop_back();

    for (int i = 0; i != c.size(); i++)
        cout << c[i] << ' ';
    cout << endl;

    for (vector<int>::iterator i = c.begin(); i != c.end(); i++)
        cout << *i << ' ';
    cout << endl;

    for (int x : c)
        cout << x << ' ';
    cout << endl;

    queue<int> q;
    priority_queue<int> pq1;                            // 大根堆
    priority_queue<int, vector<int>, greater<int>> pq2; // 小根堆
    priority_queue<pair<int, int>> pq3;
    priority_queue<Rec> pq4;

    q.push(1);
    q.pop();

    pq1.push(1);
    cout << pq1.top() << endl;
    pq1.pop();

    stack<int> stk;
    stk.push(1);
    stk.pop();
    stk.top();

    deque<int> d;
    d.push_front(1), d.push_back(2);

    set<int> e;      // 元素不能重复
    multiset<int> f; // 元素可以重复
    e.insert(1);
    if (e.find(1) == e.end())
        ; // 判断1在e中是否存在
    //set<int>::iterator it = e.begin();

    cout << "Look at here!" << endl;

    pair<int, string> p1, p2;
    p1 = {16, "wqz"};
    p2 = {33, "wqz"};
    cout << (p1 > p2) << endl;
    cout << p1.first << ' ' << p1.second << endl; // 双关键词的字典序比较

    map<string, vector<int>> g;
    g["wqz"] = vector<int>({1, 2, 3, 4});
    cout << g["wqz"][2] << endl;
    g.insert({"zm", {}});

    unordered_set<int> h;      // 哈希表，不能存储重复元素
    unordered_multiset<int> i; // 哈希表，可以存储重复元素

    unordered_map<int, int> j; // 效率更高的map

    bitset<1000> k, m; // 位串
    k[0] = 1;
    cout << k.count() << endl; // 返回位串中1的个数
    m.set(1); // 把某一位设成1
    k.reset(0); // 把某一位设成0
    k |= m;
    k &= m;
}
