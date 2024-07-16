1. 平时使用电脑时，多思考常用操作，解放鼠标手！

2. 尽量选择Alt，尽量选择能联想到原英文单词的快捷键，尽量选择靠近左Alt或者右Alt的按键（优先度依次递减）

3. 免费版Quicker最多只能设置三个快捷键，请思考哪些需求是轮盘可以完成的，哪些是快捷键可以完成的（换言之，有些应用需要单独的轮盘，那么这个时候就要用快捷键）

4. 常用快捷键：

   Alt+A：截图，来源：Snipaste

   Ctrl+B：tmux中输命令的前摇，顺便，-是上下切割，\是左右切割

   设置方法：
   
```xml
# 保存到文件 ~/.tmux.conf
set -g mouse on
unbind -n MouseDrag1Pane
unbind -Tcopy-mode MouseDrag1Pane

unbind '"'
bind - splitw -v -c '#{pane_current_path}'

unbind %
bind \\ splitw -h -c '#{pane_current_path}'
setw -g mode-keys vi
# tmux source ~/.tmux.conf
```

   Alt+C：浏览器网页全文翻译，来源：沉浸式翻译

   Alt+F：简悦，聚焦模式

   Alt+G：规范复制，来源：自制Quicker动作

   ALt+L：剪切板最新内容翻译，弹出独立窗口，来源：沙拉查词+Quicker[动作](https://getquicker.net/Sharedaction?code=b0d1a134-8284-4a44-d1be-08d746da5869)

   Ctrl+Alt+M：使用算法扩大活动窗口的分辨率，来源：Magpie

   Ctrl+Alt+↑↓←→P：网易云原生全局快捷键

   Alt+R：简悦，阅读模式

   Win+Alt+R：Windows Game Bar的视频录制快捷键，但是Game Bar需要等待一段启动时间。顺便，在Potplayer中使用Ctrl+Alt+R进行录制，使用Ctrl+E（源画面）或Ctrl+Alt+E（实画面）进行截图

   Alt+O：OCR，来源：Quicker[动作](https://getquicker.net/Sharedaction?code=7f77f60e-8bd4-41d7-3817-08d69616d953)

   Alt+Space：快速搜索，支持wox支持的功能，但是来源：Quicker

   Ctrl+Alt+/：开启代理

   Alt+F4：Windows原生快捷键，关闭当前应用

   Tab：长按+任意键 = Ctrl + 任意键，短按 = Esc，来源：[CapsLockCtrlEscape.ahk](https://gist.githubusercontent.com/sedm0784/4443120/raw/736e499ad4556eb9ae7551f111ad4350e3097f6b/CapsLockCtrlEscape.ahk)

   