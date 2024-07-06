import os

from groq import Groq

client = Groq(
    api_key=os.environ.get("GROQ_API_KEY"),
)

chat_completion = client.chat.completions.create(
    messages=[
        {
            "role": "user",
            "content": "我开启了Clash代理（并非全局模式），但我的Windows终端并没有设置代理，为什么我的终端在一定程度上可以走代理（换言之，有些命令走的是代理，有些则不是，例如ping）？请使用中文回复。",
        }
    ],
    model="llama3-70b-8192",
)

print(chat_completion.choices[0].message.content)
