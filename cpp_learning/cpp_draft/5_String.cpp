#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s = "hello world";

    for (char c: s) cout << c;
    cout << endl;
    for (char& c: s) c = 'a';
    cout << s << endl;

    return 0;
}
