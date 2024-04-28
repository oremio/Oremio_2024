@echo off
setlocal enabledelayedexpansion

:: 设置文件夹路径
set "SOURCE_DIR=E:\program2022\Leetcode\docs"

:: 检查 iconv 是否可用
iconv --version >nul 2>&1
if errorlevel 1 (
    echo iconv is not installed. Please install it first.
    exit /b 1
)

:: 转换文件
for /R "%SOURCE_DIR%" %%f in (*.htm) do (
    echo Processing: %%f
    iconv -f GB2312 -t UTF-8 "%%f" > "%%f.new"
    if errorlevel 1 (
        echo Failed to convert %%f
        del "%%f.new"
        echo Temporary file deleted: %%f.new
    ) else (
        move /Y "%%f.new" "%%f"
        echo Successfully converted %%f
    )
)

echo All files have been converted.
pause
