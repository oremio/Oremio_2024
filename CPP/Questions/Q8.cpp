// Q8：如何避免拷贝？

#include <iostream>

class Uncopyable
{
public:
    Uncopyable() {}
    ~Uncopyable() {}

    // 禁止拷贝构造函数
    Uncopyable(const Uncopyable &) = delete;
    // 禁止拷贝赋值运算符
    Uncopyable &operator=(const Uncopyable &) = delete;
};
