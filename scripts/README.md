这里存放平时写的一些小工具

2dfan_filters.py：需要一个**input.md**文件。平时留心一下2dfan的ai补丁页面，定期将最新的几页的内容，复制进markdown文件里，然后运行此程序，就会输出一个filtered_urls.md，这个文件里的补丁都是可食用的（无毒、无解压密码、可下载）

ab2tar.sh：将adb backup file的.ab格式转为tar

calculate_gkms_score.py：计算学园偶像大师的**期末考试需求分数**，接受五个参数，分别是vocal, dance, visual, 考试排名（默认考第一）和目标级别（默认a+），最后一个参数还支持b和s（前者用于游戏开服早期印彩卡，后者用于游戏开服早期凹S评分）

compare_two_folders.py：字面意思。注意**硬编码一下要比较的文件夹**

convert_avif.py：将avif文件转换为png文件，默认**当前文件夹**

del_all.py：批量删除文件，注意**硬编码一下要删除的文件夹**

find_ffmpeg.ps1：不知道咋找环境变量里有没有ffmpeg的路径，随手写了个

img_append_vertical.py：将**当前文件夹**里的所有图片纵向拼接（按照时间顺序），使用者保证图片的宽度一致

miniterm.py：PySerial附带的调试小工具，没有plink好用。

mkv2gif.bat：字面意思。直接转换当前目录下唯一的视频文件，生成gif的分辨率为800: -1，生成之后自动调用screen2gif（硬编码目录）进行后续编辑

move_files.py：将input.txt文件中的文件名提取，然后把当前目录中的对应文件全部挑出来，放到moved_files这个文件夹里

remove_black_borders：网上偷的。没用过

remove_files_0_9_jpg.bat：将名字为0, ... ,9的jpg文件的名字批量改成00, ... , 09

rename_images_from_txt.py：当前目录里，有一些txt文件和一些图片文件（后缀是jpg, jpeg, png），它们是**一一对应**的（也就是每一个txt文件都能找到一个和它的名字相等的图片文件）。它能修改每个图片文件的名字，它们的新名字由与之对应的txt文件中的内容决定。由于txt文件中的内容可能很复杂，只提取其中的前31个字符的汉字或英文（特指26个英文字母）作为图片文件的新名字。用途：配合umi_ocr使用

rename_images.py：批量重命名**截图**文件，优先使用自己名字里已有的时间戳，其次使用EXIF中的时间戳，再次使用OS记录的时间戳（这个肯定有），为了防止名字冲突，新文件名的结尾随机生成六个字符

SerialTest.ps1：linux的ansi相关知识还有待学习！

trim_borders：去除**当前文件夹**里的所有图片的黑色边缘，输出到cropped_images这一文件夹
