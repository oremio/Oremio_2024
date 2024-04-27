#include <iostream>
#include <memory>

using namespace std;

struct destination
{
};
struct connection
{
};
connection *connect(destination *);
void disconnect(connection *);
void f(destination &d)
{
    auto del_c = [](connection *c)
    { disconnect(c); delete c; };

    // d是栈上对象的引用，我们在堆上为它创建一个connection对象
    connection *c = connect(&d);
    shared_ptr<connection> pc(c, del_c);
}

/*
虽然是C++Primer的作业，但这种写法还是很难绷，d在栈上，c在堆上
保证c和d的生存期一致又是个大问题
其实改法也很简单，把f的函数签名改下就行
*/
