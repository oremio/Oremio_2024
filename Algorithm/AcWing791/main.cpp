// url: https://www.acwing.com/problem/content/793/
// tutorial: https://www.acwing.com/video/233/

/*
C++如何存储大整数？
    数组！
如何计算高精度加法？
    模拟手算！
*/

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1e6 + 10;

vector<int> add(vector<int> &A, vector<int> &B)
{
    vector<int> C;

    int t = 0;
    for (int i = 0; i < A.size() || i < B.size(); i++)
    {
        if (i < A.size())
            t += A[i];
        if (i < B.size())
            t += B[i];
        C.push_back(t % 10);
        t /= 10;
    }
    if (t)
        C.push_back(1);
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

    auto C = add(A, B);

    for (int i = C.size() - 1; i >= 0; i--)
        cout << C[i];

    return 0;
}
