rem �л���.protoЭ�����ڵ�Ŀ¼

rem ����ǰ�ļ����е�����Э���ļ�ת��Ϊlua�ļ�
set DIR=%~dp0
cd /d "%DIR%"
if not exist %DIR%..\lua mkdir %DIR%..\lua 


for %%i in (*.proto) do (  
echo %%i
protoc.exe --plugin=protoc-gen-lua="..\..\plugin\protoc-gen-lua.bat" --lua_out=../lua %%i

)
echo end
pause