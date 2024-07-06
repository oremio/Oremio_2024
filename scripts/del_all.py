import os
import shutil


def handle_remove_readonly(func, path, exc_info):
    """
    处理删除文件和目录时的权限错误。
    """
    exc_type, exc_value, exc_traceback = exc_info
    if not os.access(path, os.W_OK):
        # 如果没有写权限，尝试添加写权限
        os.chmod(path, 0o700)
        func(path)
    else:
        print(f"无视错误：{exc_value}")


def delete_folder_contents(folder_path):
    try:
        shutil.rmtree(folder_path, onerror=handle_remove_readonly)
        print(f"成功删除文件夹 {folder_path} 及其所有内容。")
    except Exception as e:
        print(f"删除文件夹 {folder_path} 出错：{e}")


if __name__ == "__main__":
    target_folder = "./backup"
    delete_folder_contents(target_folder)
