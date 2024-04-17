def divide(a, b):
    if b == 0:
        raise ZeroDivisionError("除数不能为零")
    return a / b

try:
    result = divide(10, 0)
    print("结果为:", result)
except ZeroDivisionError as e:
    print("发生除零错误:", e)

try:
    f = open("myfile.txt")
    for line in f:
        print(line)
finally:
    f.close()
