// url: https://www.nowcoder.com/practice/4b1658fd8ffb4217bc3b7e85a38cfaf2

/*
求最大连续bit数：
当一个数和自己左移一位进行位与运算，相当于和自己错开一位进行的位与运算，
如果有连续的1，经过错位位与之后会少一个1，
如果没有连续的1，错位位与之后就是0。
我们可以通过这种不断与自己的左移一位进行位与，直到为0，
什么时候结束就说明最大有多少连续的1。
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int count = 0;
    while (n) {
        n = n & (n << 1);
        count++;
    }
    cout << count << endl;
    return 0;
}
