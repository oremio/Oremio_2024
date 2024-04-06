// url: https://www.acwing.com/problem/content/3305/
// tutorial: https://www.acwing.com/video/2616/

/*
表达式求值：
用栈模拟中缀形式的二叉树
关键点：
1.二叉树叶结点都是值，内点都是运算符
2.二叉树越往上，运算符优先级越低
    换言之：我们先算乘除，再算加减，有括号则特殊处理
3.体现在栈上，则是：
    我们在读取表达式时顺便就进行入栈出栈以及计算
    如果读取到的运算符的优先级高于栈顶运算符的优先级，则说明子树还没画完
    否则说明子树已经画完，可以立刻把它算出来
*/

#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

stack<int> num;
stack<char> op;

void eval()
{
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

int main()
{
    ifstream file("input.txt");
    if (file.is_open())
    {
        // cout << "Yes" << endl;
        cin.rdbuf(file.rdbuf());
    }

    unordered_map<char, int> pr{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

    string exp;
    cin >> exp;

    int e_size = exp.size();
    for (int i = 0; i < e_size; i++)
    {
        auto c = exp[i]; // 这个auto很关键
        if (isdigit(c))
        {
            int x = 0, j = i;
            while (j < e_size && (isdigit(exp[j])))
                x = x * 10 + exp[j++] - '0';
            num.push(x); // 别忘了push新算出来的数
            i = j - 1;   // 考虑到要i++
        }
        else if (c == '(')
            op.push(c);
        else if (c == ')')
        {
            while (op.top() != '(')
                eval();
            op.pop(); // 别忘了pop'('
        }
        else
        {
            while (!op.empty() && pr[c] <= pr[op.top()]) // 读取到的运算符的优先级并未高于栈顶运算符的优先级，说明子树已经画完，可以立刻把它算出来
                eval();
            op.push(c);
        }
    }
    while (!op.empty())
        eval();
    cout << num.top() << endl;
    return 0;
}
