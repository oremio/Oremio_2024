// url: https://www.acwing.com/problem/content/871/
// tutorial: https://www.acwing.com/video/294/

/*
试除法求约数
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 110;

vector<int> get_divisor(int x){
    vector<int> res;
    for (int i = 1; i <= x / i; i++){
        if(x % i == 0){
            res.push_back(i);
            if(x / i != i)
                res.push_back(x / i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        vector<int> divi = get_divisor(x);
        int v_size = divi.size();
        for (int i = 0; i < v_size; i++)
            cout << divi[i] << ' ';
        cout << endl;
    }
    return 0;
}
