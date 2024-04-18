#include <algorithm>
#include <functional>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

namespace ns_gp
{
    void test_gp()
    {
        int ai[6] = {27, 210, 12, 47, 109, 83};     // array int
        vector<int, allocator<int>> vi(ai, ai + 6); // vector int
        /*
        vector: container
        allocator: allocator
        */
        cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40)));
        /*
        count_if: algorithm
        begin: iterator
        less: function object
        bind2nd: function adapter(binder)
        not1: function adapter(negator)(反相器)
        */
    }
}

namespace ns_hanoi
{
    const int MAX = 101;
    /*
    汉诺塔递归函数：
    入门递归的最佳算法。
    由于返回值是void，所以也不用在意return。
    1. 执行hanoi(n - 1, source, target, auxiliary)，我们将n - 1个盘子从source通过target移动到auxiliary
        因为是递归，请将这n - 1个盘子的移动方法当做黑盒，确信我们就是能做到
    2. 然后将第n个盘子放到target
    3. 执行hanoi(n - 1, auxiliary, source, target)，我们将剩下的n - 1个盘子从auxiliary通过source移动到target
        你看，我们确实能将n个盘子移动到target，对吧？
    */
    void hanoi(int n, char source, char auxiliary, char target)
    {
        if (n == 1)
        {
            std::cout << "Move disk 1 from " << source << " to " << target << std::endl;
            return;
        }
        hanoi(n - 1, source, target, auxiliary);
        std::cout << "Move disk " << n << " from " << source << " to " << target << std::endl;
        hanoi(n - 1, auxiliary, source, target);
    }
    /*
    计算汉诺塔的移动盘子的次数，又可以看成动态规划问题：
    */
    void hanoiCount(int n)
    {
        int dp[MAX];
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
            dp[i] = 1 + dp[i - 1] * 2; // 应该很好理解吧？
        std::cout << "Move counts = " << dp[n] << std::endl;
    }
    /*
    如果将汉诺塔增加到四个，那么需要移动几次呢？
    */
    void strangeHanoiCount(int n)
    {
        int dp3[MAX], dp4[MAX];
        dp3[1] = 1;
        for (int i = 2; i <= n; i++)
            dp3[i] = 1 + dp3[i - 1] * 2;

        memset(dp4, 0x3f, sizeof dp4);
        dp4[1] = 1;
        for (int i = 2; i <= n; i++)
            for (int j = 1; j < i; j++)
                dp4[i] = min(dp4[i], dp4[j] + dp3[i - j] + dp4[j]); // tutorial: https://www.acwing.com/video/115/
        std::cout << "Move counts = " << dp4[n] << std::endl;
    }

}

namespace ns_decltype
{
    //     int fun1() { return 10; }
    //     auto fun2() { return 'g'; }
    //     int main()
    //     {
    //         decltype(fun1()) x;
    //         decltype(fun2()) y = fun2();
    //         cout << typeid(x).name() << endl;
    //         cout << typeid(y).name() << endl;

    //         //--------------------------------------------------------------

    //         // auto忽略最上层的const，decltype则保留最上层的const
    //         const int x = 10;

    //         // 使用 auto 推断变量类型
    //         auto a = x; // a 的类型为 int，忽略了顶层 const
    //         a = 20;     // 合法，可以修改 a 的值
    //         std::cout << "a: " << a << std::endl;

    //         // 使用 decltype 推断变量类型
    //         decltype(x) b = x; // b 的类型为 const int，保留了顶层 const
    //         // b = 20;        // 错误！b 是常量，无法修改
    //         std::cout << "b: " << b << std::endl;

    //         //--------------------------------------------------------------

    //         // auto忽略原有类型的引用，decltype则保留原有类型的引用
    //         int x = 10;
    //         int &ref_x = x;

    //         // 使用 auto 推断变量类型
    //         auto a = ref_x;                       // a 的类型为 int，忽略了原有类型的引用
    //         a = 20;                               // 修改 a 的值不影响原有变量 x
    //         std::cout << "a: " << a << std::endl; // 输出 20
    //         std::cout << "x: " << x << std::endl; // 输出 10

    //         // 使用 decltype 推断变量类型
    //         decltype(ref_x) b = ref_x;            // b 的类型为 int&，保留了原有类型的引用
    //         b = 30;                               // 修改 b 的值会影响原有变量 x
    //         std::cout << "b: " << b << std::endl; // 输出 30
    //         std::cout << "x: " << x << std::endl; // 输出 30

    //         //--------------------------------------------------------------

    //         // 对解引用操作，auto推断出原有类型，decltype推断出引用

    //         int x = 10;
    //         int *ptr = &x;

    //         // 使用 auto 推断变量类型
    //         auto a = *ptr;                        // a 的类型为 int，推断出原有类型
    //         a = 20;                               // 修改 a 的值不影响原有变量 x
    //         std::cout << "a: " << a << std::endl; // 输出 20
    //         std::cout << "x: " << x << std::endl; // 输出 10

    //         // 使用 decltype 推断变量类型
    //         decltype(*ptr) b = *ptr;              // b 的类型为 int&，推断出引用
    //         b = 30;                               // 修改 b 的值会影响原有变量 x
    //         std::cout << "b: " << b << std::endl; // 输出 30
    //         std::cout << "x: " << x << std::endl; // 输出 30

    //         return 0;
    //     }
}

namespace ns_override
{
    class A
    {
    public:
        virtual void foo() {}
        void bar() {}
    };

    class B : public A
    {
    public:
        void foo() override {} // OK ： B::foo 覆写 A::foo
    };
}

#include <typeinfo>

namespace ns_typeid
{
    // 与 RTTI 相关的还有 typeid 运算符，返回 type_info 的引用，该类定义在标准库中。
    // 如果表达式的类型包含了虚函数，那么 typeid 在返回类型时会进行动态计算；否则在编译时就可以计算。
    class Base
    {
    public:
        virtual void func() {}
    };

    class Derived : public Base
    {
    };

    int main()
    {
        Base base_obj;
        Derived derived_obj;

        Base *ptr_base = &derived_obj;

        // 对于包含虚函数的类型，typeid 在运行时进行动态计算
        std::cout << "Type of base_obj: " << typeid(base_obj).name() << std::endl;       // 运行时计算
        std::cout << "Type of derived_obj: " << typeid(derived_obj).name() << std::endl; // 运行时计算
        std::cout << "Type of ptr_base: " << typeid(*ptr_base).name() << std::endl;      // 运行时计算

        // 对于不包含虚函数的类型，typeid 在编译时确定
        int i = 10;
        std::cout << "Type of i: " << typeid(i).name() << std::endl; // 编译时确定

        return 0;
    }
}

