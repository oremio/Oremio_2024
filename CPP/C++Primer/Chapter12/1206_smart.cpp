#include <iostream>
#include <vector>
#include <memory>

using namespace std;

unique_ptr<vector<int>> ReturnNewVector()
{
    return make_unique<vector<int>>();
}

void AssignVector(unique_ptr<vector<int>>& input)
{
    int x;
    while (cin >> x)
        input->push_back(x);
}

void PrintVector(const unique_ptr<vector<int>>& input)
{
    for (int i : *input)
        cout << i << ' ';
    cout << endl;
}

int main()
{
    auto vp = ReturnNewVector(); // 自动管理 vector<int> 的生命周期
    AssignVector(vp);
    PrintVector(vp);
    // 不需要手动 delete，智能指针会自动处理
    return 0;
}
