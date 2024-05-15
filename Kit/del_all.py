import shutil

def delete_folder_contents(folder_path):
    try:
        shutil.rmtree(folder_path)
        print(f"成功删除文件夹 {folder_path} 及其所有内容。")
    except Exception as e:
        print(f"删除文件夹 {folder_path} 出错：{e}")

if __name__ == "__main__":
    target_folder = "./ipch"
    delete_folder_contents(target_folder)
