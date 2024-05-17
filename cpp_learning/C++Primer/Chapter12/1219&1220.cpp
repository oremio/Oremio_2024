#include "StrBlob.h"
#include "StrBlobPtr.h"
#include <fstream>
#include <iostream>

using namespace std;

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

int main()
{
    ifstream file("input.txt");

    StrBlob sb;
    string tmp;
    while (getline(file, tmp))
        sb.push_back(tmp);

    StrBlobPtr sbp(sb);
    while (sbp != sb.end()) {
        cout << *sbp;
        ++sbp;
    }
    return 0;
}

/*
hello, world!
*/
