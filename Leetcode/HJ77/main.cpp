#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

const int N = 15;

/*
复盘时的聊天记录：
入站顺序，存一下，check的时候要用到
然后为了写字典顺序的全排列，我们要把火车号排序一下，然后递归写出来
所以是这么四个数组，train存排序后的火车号，train_in存入站顺序，visited和out都是递归时要用到
*/

int n;

int train[N]; // 存储各号的火车

int train_in[N]; // 存储各号的火车的进站顺序

int visited[N];
int out[N]; // 出站序列号

bool check(int* out) {
    int idx = 0;
    stack<int> st;
    for (int i = 0; i < n; i++) {
        st.push(train_in[i]);
        while (!st.empty() && st.top() == out[idx]) {
            st.pop();
            idx++;
        }
    }
    if (idx == n) return true;
    else return false;
}

void traversal(int cnt) { // cnt == 进过站的火车数
    if (cnt == n) {
        if (check(out)) {
            for (int i = 0; i < n; i++)
                cout << out[i] << ' ';
            cout << endl;
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        int tmp = train[i];
        if (!visited[tmp]) {
            visited[tmp] = 1;
            out[cnt] = tmp;
            traversal(cnt + 1);
            visited[tmp] = 0;
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> train[i];
        train_in[i] = train[i];
    }
    sort(train, train + n);
    traversal(0);
    return 0;
}
