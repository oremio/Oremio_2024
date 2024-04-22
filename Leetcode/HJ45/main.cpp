// url: https://www.nowcoder.com/practice/02cb8d3597cf416d9f6ae1b9ddc4fde3

#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <fstream>
using namespace std;

int n;
int f[30];

int main() {
    ifstream file("input.txt");
    if (file.is_open()) {
        cin.rdbuf(file.rdbuf());
    }

    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        memset(f, 0, sizeof(f));

        int s_size = s.size();
        for (int i = 0; i < s_size; i++) {
            f[s[i] - 'a']++;
        }

        int cnt = 26, sum = 0;
        sort(f, f + 26, greater<int>());
        for (int i = 0; i < 26; i++) {
            if (f[i] == 0) break;
            sum = f[i] * cnt + sum;
            cnt--;
        }
        cout << sum << endl;
    }
}
