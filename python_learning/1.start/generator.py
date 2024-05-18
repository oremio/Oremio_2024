from typing import Generator, Union

def process_numbers() -> Generator[int, Union[int, None], float]:
    total = 0
    count = 0
    while True:
        number = yield total  # 生成当前总计数并暂停
        if number is None:  # 如果接收到 None，生成器完成并返回平均值
            return total / count if count > 0 else 0.0
        total += number  # 将接收到的整数加到总计数中
        count += 1


# 使用生成器
gen = process_numbers()
print(next(gen))  # 初始化生成器并获取第一个总计数 => 0

print(gen.send(10))  # 发送 10 并获取新的总计数 => 10
print(gen.send(20))  # 发送 20 并获取新的总计数 => 30
print(gen.send(30))  # 发送 30 并获取新的总计数 => 60

try:
    print(gen.send(None))  # 发送 None 以结束生成器并获取平均值
except StopIteration as e:
    print(f"Average: {e.value}")  # 获取返回值 => Average: 20.0
