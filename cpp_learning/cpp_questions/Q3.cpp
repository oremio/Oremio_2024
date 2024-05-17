// Q3：如何限制一个对象只能建立在堆上？

#include <iostream>
#include <memory> // For std::unique_ptr

class HeapOnly
{
public:
    static std::unique_ptr<HeapOnly> create()
    {
        return std::unique_ptr<HeapOnly>(new HeapOnly());
    }
    ~HeapOnly()
    {
        std::cout << "HeapOnly destructor" << std::endl;
    }

protected:
    HeapOnly()
    {
        std::cout << "HeapOnly constructor" << std::endl;
    }

    // 禁用拷贝和赋值
    HeapOnly(const HeapOnly &) = delete;
    HeapOnly &operator=(const HeapOnly &) = delete;

    // 禁用移动构造和移动赋值
    HeapOnly(HeapOnly &&) = delete;
    HeapOnly &operator=(HeapOnly &&) = delete;
};

int main()
{
    {
        auto obj = HeapOnly::create(); // 安全地在堆上创建对象
        // 不需要手动调用delete，当unique_ptr超出作用域时，自动删除
    }
    return 0;
}

/*
HeapOnly constructor
HeapOnly destructor
*/
