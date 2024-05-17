// url: https://www.acwing.com/problem/content/841/
// tutorial: https://www.acwing.com/video/265/

/*
由于要删除和修改第k个插入的值，因为我们所有的操作都是基于插入值来的。
引入pos数组：插入序号 ==> 堆序号
堆自己用heap数组存储：堆序号 ==> 堆值
再设计一个可以反推的sop数组：堆序号 ==> 插入序号
在交换堆结点时，谨记，每个堆结点的身份证是可以用堆序号i来查的，即sop数组
1.先交换pos[sop[i]]，用身份证把户口改了
2.再交换sop[i]，把身份证上的住址改了
另一个方案是，把身份证和户口用pair绑定
3.最后交换heap[i]，把家里东西搬了
*/

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int heap[N], pos[N], sop[N];
int n;
int insertPos;
int heapSize;

void heapSwap(int x, int y)
{
    swap(pos[sop[x]], pos[sop[y]]);
    swap(sop[x], sop[y]);
    swap(heap[x], heap[y]);
}

void down(int a)
{
    int tmp = a;
    if (2 * a <= heapSize && heap[2 * a] < heap[tmp])
        tmp = 2 * a;
    if (2 * a + 1 <= heapSize && heap[2 * a + 1] < heap[tmp])
        tmp = 2 * a + 1;
    if (a != tmp)
    {
        heapSwap(a, tmp);
        down(tmp); // 别忘了继续down下去
    }
}

void up(int a)
{
    while (a / 2 && heap[a / 2] > heap[a])
    {
        heapSwap(a / 2, a);
        a /= 2;
    }
}

void insert(int x)
{
    pos[++insertPos] = heapSize;
    sop[++heapSize] = insertPos;
    heap[heapSize] = x;
    up(heapSize);
}

int putM()
{
    return heap[1];
}

void deleteM()
{
    heapSwap(1, heapSize);
    heapSize--;
    down(1);
}

void deleteK(int k)
{
    int tmp = pos[k];
    heapSwap(tmp, heapSize);
    heapSize--;
    down(tmp);
    up(tmp);
}

void correctK(int k, int x)
{
    heap[pos[k]] = x;
    down(pos[k]);
    up(pos[k]);
}

int main()
{
    // ifstream file("input.txt");
    // if (file.is_open())
    // {
    //     cin.rdbuf(file.rdbuf());
    // }

    cin >> n;
    while (n--)
    {
        string op;
        cin >> op;
        if (op == "I")
        {
            int x;
            cin >> x;
            insert(x);
        }
        else if (op == "PM")
            cout << putM() << endl;
        else if (op == "DM")
            deleteM();
        else if (op == "D")
        {
            int k;
            cin >> k;
            deleteK(k);
        }
        else
        {
            int k, x;
            cin >> k >> x;
            correctK(k, x);
        }
    }
}
