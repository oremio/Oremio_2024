// Q10：string类的构造，析构，拷贝函数？

/*
归根结底：
1. 函数签名写对，别忘了传引用和const
2. 两个成员变量，m_data，m_length，处理好
*/

#include <cstring>
#include <iostream>

class MyString
{
private:
    char *m_data;
    int m_length;

public:
    // 默认构造函数
    MyString() : m_data(new char[1]), m_length(0)
    {
        m_data[0] = '\0';
    }

    // 参数化构造函数
    MyString(const char *str)
    {
        m_length = strlen(str);
        m_data = new char[m_length + 1];
        strcpy(m_data, str);
    }

    // 拷贝构造函数
    MyString(const MyString &other)
    {
        m_length = other.m_length;
        // if (m_length > 0)
        // {
            m_data = new char[m_length + 1];
            strcpy(m_data, other.m_data);
        // }
        // else
        // {
        //     m_data = new char[1];
        //     m_data[0] = '\0';
        // }
    }

    // 拷贝赋值运算符
    MyString &operator=(const MyString &other)
    {

        // 注意！
        if (&other == this)
            return *this;

        delete[] m_data; // 所谓赋值，就是先删原值，再赋新值
        m_length = other.m_length;
        // if (m_length > 0)
        // {
            m_data = new char[m_length + 1];
            strcpy(m_data, other.m_data);
        // }
        // else
        // {
        //     m_data = new char[1];
        //     m_data[0] = '\0';
        // }

        return *this;
    }

    // 析构函数
    ~MyString()
    {
        delete[] m_data;
    }
};
