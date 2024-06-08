import os
import shutil

# 读取input.txt文件中的文件名
with open("input.txt", "r", encoding="utf-8") as f:
    filenames = f.readlines()

# 去除每行末尾的换行符
filenames = [filename.strip() for filename in filenames]

# 创建一个新的文件夹用于存放移动后的文件
if not os.path.exists("moved_files"):
    os.makedirs("moved_files")

# 遍历文件名列表，查找并移动文件
for filename in filenames:
    # 拼接文件的绝对路径
    file_path = os.path.abspath(filename)

    # 检查文件是否存在
    if os.path.exists(file_path):
        # 移动文件到新的文件夹中
        shutil.move(file_path, os.path.join("moved_files", os.path.basename(file_path)))
        print(f"Moved {filename} to moved_files folder.")
    else:
        print(f"File {filename} not found.")

print("All files moved.")
