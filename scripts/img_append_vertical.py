from PIL import Image
import os

def merge_images(input_folder, output_filename):
    images = []

    # 遍历当前文件夹内的所有图片文件，并按修改时间排序
    for filename in sorted(os.listdir(input_folder), key=lambda x: os.path.getmtime(os.path.join(input_folder, x))):
        if filename.endswith(('.png', '.jpg', '.jpeg')):
            image_path = os.path.join(input_folder, filename)
            img = Image.open(image_path)
            images.append(img)

    # 获取图片的宽度和所有图片的总高度
    width, total_height = images[0].size
    for img in images[1:]:
        total_height += img.size[1]

    # 创建新的输出图片对象
    output_img = Image.new('RGB', (width, total_height))

    # 将所有图片拼接到一起
    y_offset = 0
    for img in images:
        output_img.paste(img, (0, y_offset))
        y_offset += img.size[1]

    # 保存拼接后的图片
    output_img.save(output_filename)
    print(f"已将所有图片按时间顺序拼接并保存为 {output_filename}")

# 获取当前文件夹路径
current_folder = os.getcwd()

# 拼接输出文件路径
output_filename = os.path.join(current_folder, "output.png")

# 调用函数进行图片拼接
merge_images(current_folder, output_filename)
