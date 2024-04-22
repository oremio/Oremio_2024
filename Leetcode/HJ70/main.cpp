// url: https://www.nowcoder.com/practice/15e41630514445719a942e004edc0a5b
// 值得一提：这题一遍过编译，并且直接AC

#include <iostream>
#include <stack>
using namespace std;

const int N = 20;
struct Matrix {
    int row, col;
} m[N];

stack<Matrix> sm;
stack<char> op;

int eval() {
    int row2 = sm.top().row, col2 = sm.top().col;
    sm.pop(), op.pop();
    int row1 = sm.top().row, col1 = sm.top().col;
    sm.pop(), op.pop();
    int r = row1, l = col2;
    sm.push({r, l});
    if (op.top() != '(')
        op.push('@');
    int sum = r * l * col1;
    return sum;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> m[i].row >> m[i].col;
    }
    string s;
    cin >> s;
    int len = s.size(), sum = 0;
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(') op.push(c);
        else if (c == ')') {
            while (op.top() != '(') {
                sum += eval();
            }
            op.pop();
            op.push('@');
        }
        else {
            op.push(c);
            sm.push(m[c - 'A']);
        }
    }
    cout << sum << endl;
    return 0;
}
