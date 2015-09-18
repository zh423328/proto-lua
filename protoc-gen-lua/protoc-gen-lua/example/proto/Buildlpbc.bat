rem 切换到.proto协议所在的目录

rem 将当前文件夹中的所有协议文件转换为pb文件
@echo off
set DIR=%~dp0
cd /d "%DIR%"
setlocal enabledelayedexpansion
for /r %%i in (*.proto) do ( 
	  set pbname=%%i 
      set pbname=!pbname:~0,-6!pb
	  protoc.exe  -I %DIR% -o !pbname! %%i
)

rem copy
move *.pb %DIR%../pb 

echo "finished"
pause