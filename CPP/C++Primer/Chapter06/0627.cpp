#include <iostream>

using namespace std;

int GetSum(initializer_list<int> il)
{
    int sum = 0;
    for (const auto &i : il)
    { // 在使用initializer_list对象时，将循环控制变量声明为const引用类型，以最大程度地减少不必要的复制操作。
        sum += i;
    }
    return sum;
}
