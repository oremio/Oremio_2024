import re
import time

import requests
from bs4 import BeautifulSoup
from requests.adapters import HTTPAdapter
from requests.packages.urllib3.util.retry import Retry

# 读取 input.md 文件中的所有内容
with open("input/2dfan_input.md", "r", encoding="utf-8") as file:
    content = file.read()

# 使用正则表达式提取所有链接
pattern = re.compile(r"\[.*?\]\((http[s]?://.*?)\)")
urls = pattern.findall(content)

# 设置请求头，模拟浏览器
headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"
}

# 创建一个会话
session = requests.Session()

# 设置重试策略
retry_strategy = Retry(
    total=3,  # 总共重试次数
    backoff_factor=1,  # 等待时间指数增长因子 (1, 2, 4, ...)
    status_forcelist=[429, 500, 502, 503, 504],  # 重试的HTTP状态码
    allowed_methods=["HEAD", "GET", "OPTIONS"],  # 允许重试的方法
)
adapter = HTTPAdapter(max_retries=retry_strategy)
session.mount("http://", adapter)
session.mount("https://", adapter)

# 打开或创建 filtered_urls.md 文件，以追加模式写入链接
with open("output/2dfan_filtered_urls.md", "w", encoding="utf-8") as file:
    for url in urls:
        try:
            # 发送 HTTP 请求获取网页内容
            response = session.get(url, headers=headers)
            response.raise_for_status()
            page_content = response.text

            # 使用 BeautifulSoup 解析网页内容
            soup = BeautifulSoup(page_content, "html.parser")
            text = soup.get_text()

            # 检查网页内容是否符合条件
            if "本地载点" not in text and "网盘载点" not in text:
                print(f"不包含 '本地载点' 或 '网盘载点' : {url}")
            elif text.count("安全") < 4:
                print(f"未通过安全评估: {url}")
            elif "码" in text:
                print(f"不通过，因为需要解压: {url}")
            else:
                # 符合条件的链接写入文件
                file.write(url + "\n")
                file.flush()  # 刷新文件缓冲
                print(f"通过: {url}")

            # 增加请求间隔，避免频繁请求
            time.sleep(1)
        except requests.RequestException as e:
            print(f"无法访问 {url}: {e}")

print("筛选完成，符合条件的链接已保存到 output/2dfan_filtered_urls.md 文件中。")
