// url: https://www.acwing.com/problem/content/837/
// tutorial: https://www.acwing.com/video/260/

/*
Trie树（字典树 / 单词查找树 / 前缀树）：
高效地存储和查找字符串的一种集合
*/

#include <iostream>

using namespace std;

const int N = 100010; // 字符串最大长度

int trie[N][26]; // 最大26叉树
int idx;         // 可以看成是每个字符串的身份证，注意，idx = 0时是根节点的同时也保证是空节点
int cnt[N];      // 相同字符串计数

void insert_trie(string s)
{
    int len = s.size();
    int p = 0;
    for (int i = 0; i < len; i++)
    {
        int u = s[i] - 'a';
        if (!trie[p][u])
            trie[p][u] = ++idx; // ++idx说明字符串的身份证号从1开始
        p = trie[p][u];
    }
    cnt[p]++;
}

int query_trie(string s) {
    int len = s.size();
    int p = 0;
    for (int i = 0; i < len; i++) {
        int u = s[i] - 'a';
        if(!trie[p][u])
            return 0;
        p = trie[p][u];
    }
    return cnt[p];
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char op;
        string s;
        cin >> op >> s;
        if (op == 'I')
            insert_trie(s);
        else
            cout << query_trie(s) << endl;
    }
    return 0;
}
