#include "StrBlob.h"
#include <iostream>

using namespace std;

int main()
{
    StrBlob b1;
    {
        StrBlob b2 = {"a", "b", "c"};
        b1 = b2;
        cout << b1.size() << endl
             << b2.size() << endl;
        b2.push_back("d");
    }
    cout << b1.size() << endl;
    return 0;
}
