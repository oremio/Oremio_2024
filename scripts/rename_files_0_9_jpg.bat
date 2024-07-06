@echo off
setlocal enabledelayedexpansion

for /L %%i in (0,1,9) do (
    set "oldname=%%i.jpg"
    set "newname=0%%i.jpg"
    if exist "!oldname!" (
        ren "!oldname!" "!newname!"
    )
)
endlocal
