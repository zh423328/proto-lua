rem �л���.protoЭ�����ڵ�Ŀ¼

rem ����ǰ�ļ����е�����Э���ļ�ת��Ϊpb�ļ�
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