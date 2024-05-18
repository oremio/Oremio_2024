# Python：输入一个整数？

# 方法一：使用 int 函数转换输入

num = int(input())
print("{}\n{}".format(num, type(num)))

# 方法二：使用 map 函数
# 可以使用 map 函数将输入直接转换为 int 类型，这在处理多个输入值时尤其有用。

# 读取多个整数
nums = list(map(int, input().split()))
print(nums)

