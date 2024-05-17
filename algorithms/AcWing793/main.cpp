// url: https://www.acwing.com/problem/content/795/
// tutorial: https://www.acwing.com/video/235/

/*
123 × 12 = ？
手算的时候，我们会先算123 × 2，再算123 × 1
而下面的代码则是把12看作一个整体，其过程与我们手算12 × 123（也就是两个数换个位置再手算）类似
*/

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<int> mul(vector<int> &A, int b)
{
    vector<int> C;

    int t = 0;
    for (int i = 0; i < A.size() | t; i++)
    {
        if (i < A.size())
            t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }

    return C;
}

int main()
{
    // ifstream file("input.txt");
    // if (file.is_open())
    // {
    //     cin.rdbuf(file.rdbuf());
    // }

    string a; // 被乘数一位位算
    int b;    // 乘数比被乘数小，看作一个整体
    cin >> a >> b;

    if (!b)
    {
        cout << 0;
        return 0;
    }

    vector<int> A;
    for (int i = a.size() - 1; i >= 0; i--)
        A.push_back(a[i] - '0');

    auto C = mul(A, b);

    for (int i = C.size() - 1; i >= 0; i--)
        cout << C[i];

    return 0;
}
