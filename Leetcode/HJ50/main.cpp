// url: https://www.nowcoder.com/practice/9999764a61484d819056f807d2a91f1e

#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

stack<int> num;
stack<char> op;

void eval() {
    int b = num.top();
    num.pop();
    int a = num.top();
    num.pop();
    char c = op.top();
    op.pop();
    int x;
    if (c == '+')
        x = a + b;
    else if (c == '-')
        x = a - b;
    else if (c == '*')
        x = a * b;
    else
        x = a / b;
    num.push(x);
}

int main() {
    ifstream file("input.txt");
    if (file.is_open())
        cin.rdbuf(file.rdbuf());

    string exp;
    cin >> exp;
    unordered_map<char, int> pr{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

    // -3+2*{1+2*[(-4)/(8-6)+7]}

    int e_size = exp.size();
    for (int i = 0; i < e_size; i++) {
        auto c = exp[i];
        if (i == 0 && c == '-') {
            num.push(0);
            op.push('-');
        } else if (isdigit(c)) {
            int j = i, x = 0;
            while (j < e_size && isdigit(exp[j]))
                x = x * 10 + exp[j++] - '0';
            num.push(x);
            i = j - 1; // 考虑到i++
        } else if (c == '(' || c == '[' || c == '{') {
            op.push(c);
            if (exp[i + 1] == '-') {
                num.push(0);
                op.push('-');
                i++;
            }
        } else if (c == ')' || c == ']' || c == '}') {
            auto sym_c = op.top();
            while (sym_c != '(' && sym_c != '[' && sym_c != '{') {
                eval();
                sym_c = op.top();
            }
            op.pop();
        } else {
            while (!op.empty() && pr[c] <= pr[op.top()])
                eval();
            op.push(c);
        }
    }
    while (!op.empty())
        eval();
    cout << num.top() << endl;
    return 0;
}
