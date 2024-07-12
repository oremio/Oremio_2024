import os
import random
import re
import string
from datetime import datetime

import exifread
from PIL import Image

# 定义支持的图片扩展名
image_extensions = [".jpg", ".jpeg", ".png", ".gif"]


# 生成一个随机的6字符字符串
def generate_random_string(length=6):
    return "".join(random.choices(string.ascii_letters + string.digits, k=length))


# 从文件名中提取14个数字，并转换为YYYY-MM-DD_HH-MM-SS格式
def extract_timestamp_from_filename(filename):
    match = re.findall(r"\d", filename)
    if len(match) >= 14:
        # 提取前14个数字
        timestamp_digits = "".join(match[:14])
        # 格式化为YYYY-MM-DD_HH-MM-SS
        return f"{timestamp_digits[:4]}-{timestamp_digits[4:6]}-{timestamp_digits[6:8]}_{timestamp_digits[8:10]}-{timestamp_digits[10:12]}-{timestamp_digits[12:14]}"
    return None


# 获取图片的EXIF信息中的拍摄时间
def get_image_timestamp(filepath):
    try:
        with open(filepath, "rb") as f:
            tags = exifread.process_file(f, stop_tag="EXIF DateTimeOriginal")
            date_taken = tags.get("EXIF DateTimeOriginal")
            if date_taken:
                # EXIF DateTimeOriginal format: 'YYYY:MM:DD HH:MM:SS'
                date_taken = str(date_taken)
                date_taken = date_taken.replace(":", "-", 2).replace(" ", "_")
                return date_taken
    except Exception as e:
        print(f"Error reading EXIF data from {filepath}: {e}")
    return None


# 获取文件的修改时间并格式化为YYYY-MM-DD_HH-MM-SS
def get_file_modification_time(filepath):
    mod_time = os.path.getmtime(filepath)
    return datetime.fromtimestamp(mod_time).strftime("%Y-%m-%d_%H-%M-%S")


# 遍历当前目录的所有文件
for filename in os.listdir("."):
    file_extension = os.path.splitext(filename)[1].lower()

    if file_extension in image_extensions:
        # 尝试从文件名中提取时间戳
        timestamp = extract_timestamp_from_filename(filename)

        # # 如果没有找到14个数字的时间戳，则从EXIF信息中获取（仅对支持的格式）
        # if not timestamp and file_extension in ['.jpg', '.jpeg', '.png']:
        #     timestamp = get_image_timestamp(filename)

        # 如果仍然没有找到时间戳，则使用文件的修改时间
        if not timestamp:
            timestamp = get_file_modification_time(filename)

        random_string = generate_random_string()
        new_filename = f"{timestamp}_{random_string}{file_extension}"

        # 检查新文件名是否已存在，避免冲突
        while os.path.exists(new_filename):
            random_string = generate_random_string()
            new_filename = f"{timestamp}_{random_string}{file_extension}"

        os.rename(filename, new_filename)
        print(f"Renamed: {filename} -> {new_filename}")

print("All files have been renamed.")
