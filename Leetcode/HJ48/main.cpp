#include <fstream>
#include <iostream>
using namespace std;

const int N = 1010;
const int dummy = 1e5 + 1;

int n;
int ne[N], e[N];
int dummyhead, idx;

void init()
{
    e[0] = dummy;
    ne[0] = -1;
    dummyhead = 0;
    idx = 1;
}

void add(int in, int x)
{
    for (int i = dummyhead; i != -1; i = ne[i])
    {
        if (e[i] == x)
        {
            e[idx] = in;
            ne[idx] = ne[i];
            ne[i] = idx;
            idx++;
        }
    }
}

void del(int x)
{ // 可能删除头结点
    for (int i = dummyhead; i != -1; i = ne[i])
    {
        int next = ne[i];
        if (next != -1 && e[next] == x)
        {
            ne[i] = ne[next];
        }
    }
}

int main()
{
    ifstream file("input.txt");
    if (file.is_open())
    {
        // cout << "Yes" << endl;
        cin.rdbuf(file.rdbuf());
    }

    init();
    cin >> n;

    int head_x;
    cin >> head_x;
    add(head_x, dummy);

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    int del_x;
    cin >> del_x;
    del(del_x);
    if (ne[dummyhead] != -1)
    {
        for (int i = ne[dummyhead]; i != -1; i = ne[i])
        {
            cout << e[i] << ' ';
        }
    }

    return 0;
}
