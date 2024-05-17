// ConstStrBlobPtr.h
#ifndef CONSTSTRBLOBPTR_H
#define CONSTSTRBLOBPTR_H

#include "StrBlob.h"
#include <iostream>
#include <memory>
#include <vector>

class ConstStrBlobPtr
{
public:
    ConstStrBlobPtr() : curr(0) {}
    ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    // 返回一个对const string的引用
    const std::string &operator*() const
    {
        auto p = check(curr, "dereference past end of ConstStrBlobPtr");
        return (*p)[curr];
    }

    // 前缀递增运算符
    ConstStrBlobPtr &operator++()
    {
        check(curr, "increment past end of ConstStrBlobPtr");
        ++curr;
        return *this;
    }

    // 比较运算符
    bool operator==(const ConstStrBlobPtr &other) const
    {
        auto thisPtr = this->wptr.lock();
        auto otherPtr = other.wptr.lock();
        return thisPtr == otherPtr && this->curr == other.curr;
    }

    bool operator!=(const ConstStrBlobPtr &other) const
    {
        return !(*this == other);
    }

private:
    std::shared_ptr<const std::vector<std::string>> check(std::size_t i, const std::string &msg) const
    {
        auto ret = wptr.lock();
        if (!ret)
            throw std::runtime_error("unbound ConstStrBlobPtr");
        if (i >= ret->size())
            throw std::out_of_range(msg);
        return ret;
    }

    std::weak_ptr<const std::vector<std::string>> wptr;
    std::size_t curr;
};

#endif // CONSTSTRBLOBPTR_H
