import os
import re

# 定义图片扩展名
image_extensions = [".jpg", ".jpeg", ".png"]


# 提取前31个汉字或英文字母的函数
def extract_valid_characters(text, max_length=31):
    # 只保留汉字和英文字母
    valid_characters = re.findall(r"[\u4e00-\u9fa5A-Za-z]", text)
    # 连接前 max_length 个字符
    return "".join(valid_characters[:max_length])


# 遍历当前目录中的所有文件
for filename in os.listdir("."):
    # 如果是 txt 文件
    if filename.endswith(".txt"):
        txt_filename = filename
        # 提取文件名（不包括扩展名）
        base_name = txt_filename[:-4]

        # 寻找对应的图片文件
        for ext in image_extensions:
            image_filename = base_name + ext
            if os.path.exists(image_filename):
                # 读取 txt 文件内容
                with open(txt_filename, "r", encoding="utf-8") as f:
                    content = f.read()

                # 提取前 31 个汉字或英文字母
                new_name_base = extract_valid_characters(content)

                # 生成新的图片文件名
                new_image_filename = new_name_base + ext

                # 检查新文件名是否已存在，避免冲突
                counter = 1
                original_new_image_filename = new_image_filename
                while os.path.exists(new_image_filename):
                    new_image_filename = f"{new_name_base}_{counter}{ext}"
                    counter += 1

                # 重命名图片文件
                os.rename(image_filename, new_image_filename)
                print(f"Renamed: {image_filename} -> {new_image_filename}")
                break

print("All files have been renamed.")
