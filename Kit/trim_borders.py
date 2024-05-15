from PIL import Image
import glob

for filepath in glob.iglob(r'*.jpg'):  # 修改为搜索 JPG 文件
    im = Image.open(filepath)
    # print("Processing: ", filepath, " ", im.format, im.size, im.mode)
    box = im.convert('RGB').getbbox()

    # 计算每个轴上的黑色边框大小
    y1 = box[1]
    y2 = im.size[1] - box[3]

    # 如果上下边框任一不为零，则进行裁剪
    if y1 != 0 or y2 != 0:
        box = list(box)  # 否则无法覆盖元素

        # 仅修剪上下边框
        box[1] = 0
        box[3] = im.size[1]

        cropped = im.crop(tuple(box))
        print(filepath, im.format, im.mode)
        print("裁剪: ", im.size, "->", cropped.size)
        cropped.save(filepath)  # 保存为 JPG 格式
    else:
        print("未检测到边框，跳过...")
