// Q9：单例模式？

#include <iostream>

class Singleton
{
private:
    static Singleton *instance; // 静态成员变量
    Singleton() {}              // 私有构造函数，防止外部创建对象

public:
    static Singleton *getInstance()
    { // 静态成员函数
        if (!instance)
        {
            instance = new Singleton();
        }
        return instance;
    }
};

// ↓别忘了
Singleton *Singleton::instance = nullptr; // 初始化静态成员变量

int main()
{
    Singleton *singleton1 = Singleton::getInstance();
    Singleton *singleton2 = Singleton::getInstance();

    // singleton1 和 singleton2 指向同一个实例
    return 0;
}
