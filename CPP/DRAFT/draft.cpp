#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

int main(){
    int ai[6] = {27, 210, 12, 47, 109, 83}; // array int
    vector<int, allocator<int>> vi(ai, ai + 6); // vector int
    /*
    vector: container
    allocator: allocator
    */
    cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40)));
    /*
    count_if: algorithm
    begin: iterator
    less: function object
    bind2nd: function adapter(binder)
    not1: function adapter(negator)(反相器)
    */
}
