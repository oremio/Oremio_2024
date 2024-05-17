#include "StrBlob.h"
#include "ConstStrBlobPtr.h"
#include <fstream>
#include <iostream>

using namespace std;

ConstStrBlobPtr StrBlob::begin() const
{
    return ConstStrBlobPtr(*this);
}
ConstStrBlobPtr StrBlob::end() const
{
    auto ret = ConstStrBlobPtr(*this, data->size());
    return ret;
}

int main()
{
    const StrBlob sb{"Hello,", "world!"};
    ConstStrBlobPtr sbp(sb);
    while (sbp != sb.end()) {
        cout << *sbp;
        ++sbp;
    }
    return 0;
}

/*
hello, world!
*/
