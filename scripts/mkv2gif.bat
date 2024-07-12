@echo off
setlocal

:: 初始化变量
set "inputFile="

:: 查找当前目录下唯一一个 .mkv 文件
for %%f in (*.mkv) do (
    if defined inputFile (
        echo 当前目录下有多个 .mkv 文件，请确保只有一个。
        goto :eof
    )
    set "inputFile=%%f"
)

:: 检查是否找到了一个 .mkv 文件
if not defined inputFile (
    echo 当前目录下没有找到 .mkv 文件。
    goto :eof
)

:: 提取输入文件的目录、名称和扩展名
for %%f in ("%inputFile%") do (
    set "inputDir=%%~dpf"
    set "inputName=%%~nf"
    set "inputExt=%%~xf"
)

:: 设置输出文件名
set "outputFile=%inputDir%%inputName%.gif"

:: 调用FFmpeg进行转换
ffmpeg -i "%inputFile%" -vf "fps=24,scale=800:-1:flags=lanczos,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse" -loop 0 "%outputFile%"

echo 转换完成: %outputFile%

:: 调用ScreenToGif程序，打开生成的GIF文件
start "" "E:\acgn\sources\TEMP\Library\ScreenToGif.exe" "%outputFile%"

:: 结束批处理文件
endlocal
