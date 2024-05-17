// Q6：类大小的计算？

/*
说明：程序在64位编译器下测试
*/

#include <iostream>

using namespace std;

class A
{
public:
    A() : c_var(0) {}
    A(int temp) : c_var(temp) {}                 // 不影响类的大小
    ~A() {}                                      // 不影响类的大小
    virtual void f() { cout << "A::f" << endl; } // 虚指针8字节
    // 填充4字节

private:
    static int s_var; // 不影响类的大小
    const int c_var;  // 4字节
    int var1;         // 4字节
    char var2;        // 1 + 3字节
};

class B : public A
{
public:
    virtual void g() { cout << "B::g" << endl; }
};

int A::s_var;

int main()
{
    A a(4);
    A *p = new A(4);
    cout << sizeof(a) << endl;
    cout << sizeof(p) << endl;
    cout << sizeof(*p) << endl;

    B b;
    cout << sizeof(b) << endl;
    return 0;
}

/*
24
8
24
24
*/
