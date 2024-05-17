// url: https://www.nowcoder.com/practice/5190a1db6f4f4ddb92fd9c365c944584

#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

const int N = 1010;

struct nonchar
{
    int idx;
    char c;
} nc[N];

char chars[N];
int idx_c, idx_nc;

bool isChar(char a)
{
    return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z');
}

bool isBig(char a)
{
    return a >= 'A' && a <= 'Z';
}

bool cmp(char a, char b)
{ // if a < b return 1
    if (isBig(a))
        a += 32; // 'a' - 'A' = 32
    if (isBig(b))
        b += 32;
    return a < b;
}

int main()
{
    ifstream file("input.txt");
    if (file.is_open())
    {
        cin.rdbuf(file.rdbuf());
    }

    string s;
    getline(cin, s);
    int len = s.size();

    // 一遍扫描，把字符串分成char串和非char串
    for (int i = 0; i < len; i++)
    {
        if (isChar(s[i]))
            chars[idx_c++] = s[i];
        else
            nc[idx_nc++] = {i, s[i]};
    }

    stable_sort(chars, chars + idx_c, cmp);

    for (int i = 0, cnt_c = 0, cnt_nc = 0; i < len; i++)
    {
        if (idx_nc > 0 && i == nc[cnt_nc].idx)
            cout << nc[cnt_nc++].c;
        else
            cout << chars[cnt_c++];
    }

    return 0;
}
