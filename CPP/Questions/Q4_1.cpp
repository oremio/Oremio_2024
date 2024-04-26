// Q4：什么是虚继承？为什么需要虚继承？
// 如果不用虚继承……

#include <iostream>

class A {
public:
    int value;
    A() : value(10) {}
};

class B1 : public A {};
class B2 : public A {};

class D : public B1, public B2 {};

int main() {
    D d;
    d.B1::value = 20;
    std::cout << "B1 value: " << d.B1::value << std::endl;
    std::cout << "B2 value: " << d.B2::value << std::endl;
    return 0;
}

/*
B1 value: 20
B2 value: 10
*/
