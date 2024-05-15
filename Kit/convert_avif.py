import pillow_avif
from PIL import Image
import os
import sys

def convert_avif_to_png(input_folder, output_folder):
    # 创建输出文件夹
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # 记录成功和失败的文件数量
    success_count = 0
    fail_count = 0

    # 遍历输入文件夹中的所有文件
    for filename in os.listdir(input_folder):
        if filename.endswith(".avif"):
            input_file_path = os.path.join(input_folder, filename)
            output_file_path = os.path.join(output_folder, filename[:-5] + ".png")

            # 尝试打开AVIF文件并保存为PNG格式
            try:
                image = Image.open(input_file_path)
                image.save(output_file_path)
                print(f"成功转换并保存: {filename} -> {output_file_path}")
                success_count += 1
            except Exception as e:
                print(f"转换失败: {filename}，错误信息：{str(e)}")
                fail_count += 1

    print(f"\n转换完成！成功转换的文件数：{success_count}，转换失败的文件数：{fail_count}")

# 获取输入文件夹路径
input_folder = input("请输入包含AVIF文件的文件夹路径（默认为当前目录）：")
if input_folder == "":
    input_folder = "."

# 创建输出文件夹路径
output_folder = os.path.join(input_folder, "converted_png")
print(f"将转换后的PNG文件保存到：{output_folder}")

# 调用转换函数
convert_avif_to_png(input_folder, output_folder)
