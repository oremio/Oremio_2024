import os


def find_common_files(folder1, folder2, output_file):
    # 获取文件列表
    files1 = set(os.listdir(folder1))
    files2 = set(os.listdir(folder2))

    # 找到相同文件名的文件
    common_files = files1.intersection(files2)

    # 将相同文件名的文件输出到文件中
    with open(output_file, "w", encoding="utf-8") as f:
        for file in common_files:
            f.write(file + "\n")


# 设置文件夹路径
folder1 = "F:\\ACGN\\Library"
folder2 = "E:\\acgn\\sources\\TEMP\\Meme"
output_file = "output.txt"

find_common_files(folder1, folder2, output_file)
