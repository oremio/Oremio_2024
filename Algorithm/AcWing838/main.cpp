// url: https://www.acwing.com/problem/content/840/
// tutorial: https://www.acwing.com/video/263/
// TC : nlogn

/*
0.数组的下标从1开始，想一想为什么？
1.插入一个数：
heap[++heapSize] = x;
up(heapSize); // up 最后一个数
2.求集合当中的最小值：heap[1];
3.删除最小值：
heap[1] = heap[heapSize]; // 将堆顶与堆底交换
heapSize--; // 这样就删掉了
down(1);
4.删除任意一个元素
heap[k] = heap[heapSize]; // 将k与堆底交换
heapSize--; // 这样就删掉了
down(k);
up(k);
5.修改任意一个元素
heap[k] = x;
// 这个元素要么变大，要么变小，（要么不变）down和up只会执行一个
down(k);
up(k);
*/

#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100010;
int n, m;
int heap[N];
int heapSize;

void down(int a)
{
    int tmp = a;
    if (2 * a <= heapSize && heap[2 * a] < heap[tmp])
        tmp = 2 * a;
    if (2 * a + 1 <= heapSize && heap[2 * a + 1] < heap[tmp])
        tmp = 2 * a + 1;
    if (a != tmp)
    {
        swap(heap[a], heap[tmp]);
        down(tmp); // 别忘了继续down下去
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> heap[i];

    heapSize = n; // heapSize是重要的全局变量

    for (int i = n / 2; i; i--) // O(n)的时间复杂度建堆
        down(i);

    while (m--)
    {
        cout << heap[1] << ' ';
        heap[1] = heap[heapSize];
        heapSize--;
        down(1);
    }
}
