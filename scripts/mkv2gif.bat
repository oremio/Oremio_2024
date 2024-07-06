@echo off
setlocal

:: 检查是否提供了输入文件
if "%~1"=="" (
    echo 需要提供输入文件路径。
    echo 用法: convert.bat input.mp4
    goto :eof
)

:: 获取输入文件的完整路径和名称
set "inputFile=%~1"

:: 提取输入文件的目录、名称和扩展名
set "inputDir=%~dp1"
set "inputName=%~n1"
set "inputExt=%~x1"

:: 设置输出文件名
set "outputFile=%inputDir%%inputName%.gif"

:: 调用FFmpeg进行转换
ffmpeg -i "%inputFile%" -vf "fps=24,scale=540:-1:flags=lanczos" -c:v gif "%outputFile%"

echo 转换完成: %outputFile%

:: 调用ScreenToGif程序，打开生成的GIF文件
start "" "E:\acgn\sources\TEMP\Library\ScreenToGif.exe" "%outputFile%"

:: 结束批处理文件
endlocal
