import math
import sys


def calculate_score(vocal, dance, visual, rank=1, level="a+"):
    # 初始化 sum
    sum = 0

    # 根据 rank 值更新 sum，并增加 vocal, dance, visual
    if rank == 1:
        sum += 1700
        vocal = min(vocal + 30, 1500)
        dance = min(dance + 30, 1500)
        visual = min(visual + 30, 1500)
    elif rank == 2:
        sum += 900
        vocal = min(vocal + 20, 1500)
        dance = min(dance + 20, 1500)
        visual = min(visual + 20, 1500)
    elif rank == 3:
        sum += 500
        vocal = min(vocal + 10, 1500)
        dance = min(dance + 10, 1500)
        visual = min(visual + 10, 1500)

    # 计算能力总和 ability
    ability = vocal + dance + visual

    # 计算最终的 sum
    sum += ability * 2.3

    # 根据 level 值确定 target
    if level == "a+":
        target = 11500
    elif level == "b":
        target = 6000
    elif level == "s":
        target = 13000
    else:
        raise ValueError("Invalid level value. Accepted values are 'a+', 'b', 's'.")

    # 计算 gap
    gap = target - sum

    # 根据 gap 计算 score
    if 0 < gap <= 1500:
        score = gap / 0.3
    elif 1500 < gap <= 2250:
        score = (gap - 750) / 0.15
    elif 2250 < gap <= 3050:
        score = (gap - 1450) / 0.08
    elif 3050 < gap <= 3450:
        score = (gap - 2250) / 0.04
    elif 3450 < gap <= 3650:
        score = (gap - 2850) / 0.02
    elif 3650 < gap <= 3750:
        score = (gap - 3250) / 0.01
    else:
        raise ValueError("Your ability is not enough, please remake your game.")

    # 向上取整 score
    score = math.ceil(score)

    return score


# 从命令行获取参数
if __name__ == "__main__":
    args = sys.argv[1:]

    if len(args) < 3:
        print("Please provide at least vocal, dance, and visual values.")
        sys.exit(1)

    vocal = int(args[0])
    dance = int(args[1])
    visual = int(args[2])

    rank = int(args[3]) if len(args) > 3 else 1
    level = args[4] if len(args) > 4 else "a+"

    try:
        score = calculate_score(vocal, dance, visual, rank, level)
        print(f"The score is: {score}")
    except ValueError as e:
        print(e)
