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

using ConstPointer = const unsigned long*;

// int main()
// {
//     int n = 5;                         // 盘子的数量
//     ns_hanoi::hanoi(n, 'A', 'B', 'C'); // 将n个盘子从A通过B移动到C
//     ns_hanoi::hanoiCount(n);
//     ns_hanoi::strangeHanoiCount(n);
//     return 0;
// }

#include <iostream>
using namespace std;
int fun1() { return 10; }
auto fun2() { return 'g'; }
int main(){
    decltype(fun1()) x;
    decltype(fun2()) y = fun2();
    cout << typeid(x).name() << endl;
    cout << typeid(y).name() << endl;
    return 0;
}
