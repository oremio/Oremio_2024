// url: https://www.acwing.com/problem/content/794/
// tutorial: https://www.acwing.com/video/234/

/*
如何模拟减法？
    0. A、B均为自然数
    1. 首先，我们默认A - B时，A >= B（否则我们可以B - A再取相反数）
    2. 逐位相减，注意借位
    3. 如果减出负数，记得借位，然后结果加10
*/

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// 判断是否有A >= B
bool cmp(vector<int> &A, vector<int> &B)
{
    if (A.size() != B.size())
        return A.size() > B.size();
    for (int i = A.size() - 1; i >= 0; i--)
        if (A[i] != B[i])
            return A[i] > B[i];
    return true;
}

vector<int> sub(vector<int> &A, vector<int> &B)
{
    vector<int> C;
    for (int i = 0, t = 0; i < A.size(); i++)
    {
        t = A[i] - t; // 先减个借位
        if (i < B.size())
            t -= B[i];
        C.push_back((t + 10) % 10); // 可以将两种情况合二为一
        if (t < 0)
            t = 1;
        else
            t = 0;
    }
    while (C.size() > 1 && C.back() == 0)
    /*
    - 这是一个关键点
    - C的位数一定和A相同，那么我们需要去掉C的前导零
    - 如果A和B相同，减出来是0，那我们至少得留下一位
    */
        C.pop_back();
    return C;
}

int main()
{
    // ifstream file("input.txt");
    // if (file.is_open())
    // {
    //     cin.rdbuf(file.rdbuf());
    // }

    string a, b;
    vector<int> A, B;

    cin >> a >> b; // a = "123456"
    for (int i = a.size() - 1; i >= 0; i--)
        A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--)
        B.push_back(b[i] - '0');

    if (cmp(A, B))
    {
        auto C = sub(A, B);
        for (int i = C.size() - 1; i >= 0; i--)
            cout << C[i];
    }
    else
    {
        auto C = sub(B, A);
        cout << '-';
        for (int i = C.size() - 1; i >= 0; i--)
            cout << C[i];
    }
    return 0;
}
