// Q11：完美转发？

#include <utility>

// 这个函数负责“转发”它的参数到另一个函数
template<typename T>
void wrapper(T&& arg) {
    // 使用 std::forward 来确保 arg 的值类别得以保持不变
    target(std::forward<T>(arg));
}

// 一个可能接受左值或右值参数的目标函数
void target(int& x) {
    // 处理左值
}

void target(int&& x) {
    // 处理右值
}

int main() {
    int lv = 5;     // 左值
    wrapper(lv);    // 应该调用 void target(int& x)
    wrapper(10);    // 应该调用 void target(int&& x)
}


