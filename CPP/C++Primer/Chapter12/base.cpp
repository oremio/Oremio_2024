#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// 一个由我们实现的、元素为string的动态数组
class StrBlob
{
public:
    typedef vector<string>::size_type size_type;
    StrBlob() : data(make_shared<vector<string>>()) {}
    StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>()) {}
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    // 添加和删除元素
    void push_back(const string &t) { data->push_back(t); }
    void pop_back() { data->pop_back(); }

    // 元素访问
    string &front() { return data->front(); }
    string &back() { return data->back(); }

private:
    shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg) const;
};

void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
        throw out_of_range(msg);
}
