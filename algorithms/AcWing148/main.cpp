// url: https://www.acwing.com/problem/content/150/
// tutorial: https://www.acwing.com/video/127/
// TC

/*
哈夫曼树具有最优子结构，可以采取贪心。
具有最优子结构的问题，抽象成函数都是只有一个极值的。
哈夫曼树步骤：
0.应该选择什么数据结构？答案是小根堆！
1.不断合并最小的两个元素
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int N = 10010;

int main(){
    int n;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; i++){
        int a;
        cin >> a;
        q.push(a);
    }

    int res = 0;
    while(q.size()>1){
        int a = q.top();
        q.pop();
        int b = q.top();
        q.pop();
        res += (a + b);
        q.push(a + b);
    }

    cout << res << endl;
}
