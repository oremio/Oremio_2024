#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<int> *ReturnNewVector()
{
    return new vector<int>();
}

vector<int> *AssignVector(vector<int> *input)
{
    int x;
    while (cin >> x)
        input->push_back(x);
    return input;
}

void PrintVector(vector<int> *input)
{
    for (auto i : *input)
        cout << i << ' ';
    cout << endl;
    return;
}

int main()
{
    vector<int> *vp = AssignVector(ReturnNewVector());
    PrintVector(vp);
    delete vp;
    return 0;
}
