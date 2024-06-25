1. 平时使用电脑时，多思考常用操作，解放鼠标手！

2. 尽量选择Alt，尽量选择能联想到原英文单词的快捷键，尽量选择靠近左Alt或者右Alt的按键（优先度依次递减）

3. 免费版Quicker最多只能设置三个快捷键，请思考哪些需求是轮盘可以完成的，哪些是快捷键可以完成的（换言之，有些应用需要单独的轮盘，那么这个时候就要用快捷键）

4. 常用快捷键：

   Alt+A：截图，来源：Snipaste

   Ctrl+A：tmux中输命令的前摇，顺便，-是上下切割，\是左右切割

   设置方法：
   
```xml
set -g prefix C-a                                 # 设置前缀按键 Ctrl + A。
unbind C-b                                        # 取消 Ctrl + B 快捷键。
bind C-a send-prefix                              # 第二次按下 Ctrl + A 为向 shell 发送 Ctrl + A。
                                                  # （Shell 中 Ctrl + A 表示光标移动到最前端）。
set -g mouse on                                   # 启动鼠标操作模式，随后可以鼠标拖动边界进行面板大小调整。
unbind -n MouseDrag1Pane
unbind -Tcopy-mode MouseDrag1Pane

unbind '"'                                        # 使用 - 代表横向分割。
bind - splitw -v -c '#{pane_current_path}'        # -v 代表新建的面板使用全部的宽度，效果即为横向分割（或者说，切割得到的新的面板在竖直方向 (vertical) 排列）。

unbind %                                          # 使用 \ 代表纵向分割（因为我不想按 Shift）。
bind \\ splitw -h -c '#{pane_current_path}'       # -h 则代表新建的面板使用全部的高度，效果即为纵向分割（切割得到的新的面板在水平方向 (horizontal) 排列）。
setw -g mode-keys vi                              # 设置 copy-mode 快捷键模式为 vi。
```

   Alt+K：浏览器网页全文翻译，来源：沉浸式翻译

   ALt+L：剪切板最新内容翻译，弹出独立窗口，来源：沙拉查词+Quicker[动作](https://getquicker.net/Sharedaction?code=b0d1a134-8284-4a44-d1be-08d746da5869)

   Ctrl+Alt+M：使用算法扩大活动窗口的分辨率，来源：Magpie

   Ctrl+Alt+↑↓←→P：网易云原生全局快捷键

   Alt+R：Windows Game Bar的视频录制快捷键，但是Game Bar需要等待一段启动时间。顺便，在Potplayer中使用Ctrl+Alt+R进行录制，使用Ctrl+E（源画面）或Ctrl+Alt+E（实画面）进行截图

   Alt+O：OCR，来源：Quicker[动作](https://getquicker.net/Sharedaction?code=7f77f60e-8bd4-41d7-3817-08d69616d953)

   Alt+P：规范粘贴，来源：Quicker[动作](https://getquicker.net/Sharedaction?code=cfc572a1-47c8-4fab-2457-08d6d7620f1e)

   Ctrl+W：Chrome原生快捷键，关闭标签页

   Alt+Space：快速搜索，支持wox支持的功能，但是来源：Quicker

   Ctrl+Alt+/：开启代理

   Alt+F4：Windows原生快捷键，关闭当前应用

   Tab：长按+任意键 = Ctrl + 任意键，短按 = Esc，来源：[CapsLockCtrlEscape.ahk](https://gist.githubusercontent.com/sedm0784/4443120/raw/736e499ad4556eb9ae7551f111ad4350e3097f6b/CapsLockCtrlEscape.ahk)

   