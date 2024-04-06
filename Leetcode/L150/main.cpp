// url: https://leetcode.cn/problems/evaluate-reverse-polish-notation/

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    stack<int> num;
    int eval(char c) {
        int b = num.top();
        num.pop();
        int a = num.top();
        num.pop();
        int x;
        if (c == '+')
            x = a + b;
        else if (c == '-')
            x = a - b;
        else if (c == '*')
            x = a * b;
        else
            x = a / b;
        return x;
    }
    int evalRPN(vector<string>& tokens) {
        // RPN == reverse Polish notation
        int t_size = tokens.size();
        for (int i = 0; i < t_size; i++) {
            auto c = tokens[i][0];
            if (isdigit(c)) {
                int x = 0;
                for (int j = 0; j < tokens[i].size(); j++) {
                    x = x * 10 + tokens[i][j] - '0';
                }
                num.push(x);
            }
            else if(tokens[i].size() > 1 && c == '-'){
                int x = 0;
                for (int j = 1; j < tokens[i].size(); j++) {
                    x = x * 10 + tokens[i][j] - '0';
                }
                x *= -1;
                num.push(x);
            }
            else {
                int x = eval(c);
                num.push(x);
            }
        }
        return num.top();
    }
};

int main(){
    Solution s;
    vector<string> input{"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    s.evalRPN(input);
    return 0;
}
