rem �л���.protoЭ�����ڵ�Ŀ¼

rem ����ǰ�ļ����е�����Э���ļ�ת��Ϊcpp�ļ�
set DIR=%~dp0
cd /d "%DIR%"
if not exist %DIR%..\cpp mkdir %DIR%..\cpp 

for %%i in (*.proto) do (  
echo %%i
protoc.exe  -I=./  --cpp_out=../cpp %%i
)
echo end
pause