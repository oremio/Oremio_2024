// url: https://www.acwing.com/problem/content/792/
// tutorial: https://www.acwing.com/video/232/

/*
1. m = (l + r) >> 2
2.  if(m^3 >= x) r = m
    else l = m (注意是浮点数)
*/

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    // ifstream file("input.txt");
    // if (file.is_open())
    // {
    //     cin.rdbuf(file.rdbuf());
    // }

    double x;
    cin >> x;

    // double y = 3.0;
    // cout << y << endl;

    double l = -10000, r = 10000;
    while (r - l > 1e-8)
    {
        double mid = (l + r) / 2;
        if(mid * mid * mid >= x)
            r = mid;
        else
            l = mid;
    }
    cout << std::setprecision(6) << std::fixed << l;

    return 0;
}
