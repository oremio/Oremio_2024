// Q7：智能指针循环引用的解决方法？

#include <iostream>
#include <memory>

using namespace std;

class Child;
class Parent;

class Parent
{
private:
    // shared_ptr<Child> ChildPtr;
    weak_ptr<Child> ChildPtr;

public:
    void setChild(shared_ptr<Child> child)
    {
        this->ChildPtr = child;
    }
    void doSomething()
    {
    }
};

class Child
{
private:
    shared_ptr<Parent> ParentPtr;

public:
    void setParent(shared_ptr<Parent> parent)
    {
        this->ParentPtr = parent;
    }
    void doSomething()
    {
    }
};

int main()
{
    weak_ptr<Parent> wpp;
    weak_ptr<Child> wpc;
    {
        shared_ptr<Parent> p = make_shared<Parent>();
        shared_ptr<Child> c = make_shared<Child>();
        p->setChild(c); // 不占用c的引用计数
        c->setParent(p);
        wpp = p;
        wpc = c;
        cout << p.use_count() << endl;
        cout << c.use_count() << endl;
    }
    cout << wpp.use_count() << endl;
    cout << wpc.use_count() << endl;
}
