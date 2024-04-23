// StrBlob.h
#ifndef STRBLOB_H
#define STRBLOB_H

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;

    inline StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
    inline StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

    inline size_type size() const { return data->size(); }
    inline bool empty() const { return data->empty(); }

    inline void push_back(const std::string &t) { data->push_back(t); }
    inline void pop_back()
    {
        check(0, "pop_back on empty StrBlob");
        data->pop_back();
    }

    inline std::string &front()
    {
        check(0, "front on empty StrBlob");
        return data->front();
    }

    inline const std::string &front() const
    {
        check(0, "front on empty StrBlob");
        return data->front();
    }

    inline std::string &back()
    {
        check(0, "back on empty StrBlob");
        return data->back();
    }

    inline const std::string &back() const
    {
        check(0, "back on empty StrBlob");
        return data->back();
    }

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const
    {
        if (i >= data->size())
            throw std::out_of_range(msg);
    }
};

#endif // STRBLOB_H
