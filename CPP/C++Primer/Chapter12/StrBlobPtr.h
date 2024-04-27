// StrBlobPtr.h
#ifndef STRBLOBPTR_H
#define STRBLOBPTR_H

#include "StrBlob.h"
#include <iostream>
#include <memory>
#include <vector>

class StrBlobPtr
{
public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    std::string &operator*() const
    {
        auto p = check(curr, "dereference past end of StrBlobPtr");
        return (*p)[curr];
    }
    StrBlobPtr &operator++()
    {
        check(curr, "increment past end of StrBlobPtr");
        ++curr;
        return *this;
    }
    bool operator==(const StrBlobPtr &other) const
    {
        auto thisPtr = this->wptr.lock();
        auto otherPtr = other.wptr.lock();
        return thisPtr == otherPtr && this->curr == other.curr;
    }
    bool operator!=(const StrBlobPtr &other) const
    {
        return !(*this == other);
    }

private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t i, const std::string &msg) const
    {
        auto ret = wptr.lock();
        if (!ret)
            throw std::runtime_error("unbound StrBlobPtr");
        if (i >= ret->size())
            throw std::out_of_range(msg);
        return ret;
    }
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

#endif // STRBLOBPTR_H
