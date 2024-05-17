// Q2：如何限制一个对象只能建立在栈上？
#include <iostream>

class StackOnly
{
private:
    // 将 operator new 私有化
    void *operator new(size_t) = delete;
    void *operator new[](size_t) = delete;

public:
    StackOnly()
    {
        // 构造函数
        std::cout << "StackOnly object created on stack" << std::endl;
    }

    ~StackOnly()
    {
        // 析构函数
        std::cout << "StackOnly object destroyed" << std::endl;
    }
};

int main()
{
    {   // 正确：在栈上创建对象
        StackOnly myStackObject;

        // 错误：尝试在堆上创建对象
        // StackOnly* myHeapObject = new StackOnly(); // 这行会编译错误
    }
    return 0;
}

/*
StackOnly object created on stack
StackOnly object destroyed
*/
