// url: https://www.acwing.com/problem/content/828/
// tutorial: https://www.acwing.com/video/253/

/*
用数组来表示单链表
*/

#include <fstream>
#include <iostream>

using namespace std;

const int N = 100010;

// head 表示头结点的下标
// e[i] 表示结点i的值
// ne[i] 表示结点i的next指针值
// idx 存储当前已经用到了的地址的下一个

int head, e[N], ne[N], idx;

void init()
{
    head = -1;
    idx = 0;
}

void add_to_head(int x)
{
    e[idx] = x;
    ne[idx] = head;
    head = idx;
    idx++;
}

void remove(int k)
{
    ne[k] = ne[ne[k]];
}

void insert(int k, int x)
{
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx++;
}

int main()
{
    ifstream file("input.txt");
    if (file.is_open())
    {
        cin.rdbuf(file.rdbuf());
    }

    init();

    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int k, x;
        char op;
        cin >> op;
        if (op == 'H')
        {
            cin >> x;
            add_to_head(x);
        }
        if (op == 'D')
        {
            cin >> k;
            if(k != 0)
            remove(k - 1);
            else
                head = ne[head];
        }
        if (op == 'I')
        {
            cin >> k >> x;
            insert(k - 1, x);
        }
    }
    for (int i = head; i != -1; i = ne[i]){
        cout << e[i] << ' ';
    }
        return 0;
}
