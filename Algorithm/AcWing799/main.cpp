// url: https://www.acwing.com/problem/content/801/
// tutorial: https://www.acwing.com/video/245/
// TC: n

/*
双指针算法一般分为两类，
一类可以回忆一下归并排序，另一类可以回忆一下快速排序
双指针的一个简单模板：
for(i = 0, j = 0; i < n; i++)
{
    while(j < i && check(i, j)) j++;
    // 每道题目的具体逻辑
}

双指针的核心思想：维护某一段区间
具体到本题：维护一段最长连续不重复子序列
i指针逐步往后，它指向当前判断的数
j指针在i指针左边，当i指针往后移动时，可以证明，j指针也会往后移动（而不可能往前）


关于本题的check(i, j)怎么写：设置一个字典数组，查询每个数出现的次数
e.g.
1 2 3 4 5 2 7 8 9
j i
首先 i=0，j=0
i一直往前走，j还是在0的位置，因为没有重复数字，res=5
当i=5时是2，有重复数字，则此时s[a[5]] = 2,则执行s[a[j]]–-
直到j到i的位置j=5，s[a[5]] = 1
则接下来i就可以往前走了，最终得到最长不包含重复的数的连续区间
*/

#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100010;

int n;
int num[N], s[N];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> num[i];
    int res = 0;
    for (int i = 0, j = 0; i < n; i++)
    {
        s[num[i]]++;
        while (s[num[i]] > 1)
        {
            s[num[j]]--; // 开始移动j指针
            j++;
        }
        res = max(res, i - j + 1); // 每个i指针都做一次阶段性总结，计算res
    }
    cout << res << endl;
    return 0;
}
