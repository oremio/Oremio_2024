// url : https://www.nowcoder.com/practice/f8538f9ae3f1484fb137789dec6eedb9

#include<iostream>
#include<cmath>
using namespace std;

bool isPrime(int n) { //判断数字n是否是素数
    for (int i = 2; i <= n / i; i++) { //遍历到根号n
        if (n % i == 0)
            return false;
    }
    return true;
}

int main() {
    int n;
    while (cin >> n) {
        int mindis = n;
        pair<int, int> res; //记录两个素数
        for (int i = n / 2; i > 1; i--) { //从n的中间开始找
            if (isPrime(i) &&
                    isPrime(n - i)) { //第一次遇见两个数都是素数的时候距离从小
                cout << i << endl << n - i << endl;
                break;
            }
        }
    }
    return 0;
}
