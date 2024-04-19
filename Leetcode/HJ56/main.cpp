// url: https://www.nowcoder.com/practice/7299c12e6abb437c87ad3e712383ff84

/*
方法：试除法求约数，并顺便算和
*/

#include <iostream>
using namespace std;

int get_divisor_sum(int x)
{
    if (x == 1) // 特殊处理一下1
        return 0;
    int sum = 0;
    for (int i = 1; i <= x / i; i++)
    {
        if (x % i == 0)
        {
            sum += i;
            if (i != 1 && x / i != i)
                sum += (x / i);
        }
    }
    return sum;
}

int main()
{
    int n, cnt = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        if (i == get_divisor_sum(i))
            cnt++;
    }
    cout << cnt << endl;
    return 0;
}
