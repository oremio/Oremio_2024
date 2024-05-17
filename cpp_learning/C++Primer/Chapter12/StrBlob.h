// StrBlob.h
#ifndef STRBLOB_H
#define STRBLOB_H

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob
{
public:
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;
    typedef std::vector<std::string>::size_type size_type;

    StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
    StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back()
    {
        check(0, "pop_back on empty StrBlob");
        data->pop_back();
    }

    std::string &front()
    {
        check(0, "front on empty StrBlob");
        return data->front();
    }

    const std::string &front() const
    {
        check(0, "front on empty StrBlob");
        return data->front();
    }

    std::string &back()
    {
        check(0, "back on empty StrBlob");
        return data->back();
    }

    const std::string &back() const
    {
        check(0, "back on empty StrBlob");
        return data->back();
    }
    StrBlobPtr begin();
    StrBlobPtr end();
    ConstStrBlobPtr begin() const;
    ConstStrBlobPtr end() const;

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const
    {
        if (i >= data->size())
            throw std::out_of_range(msg);
    }
};

#endif // STRBLOB_H
