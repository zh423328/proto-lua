rem �л���.protoЭ�����ڵ�Ŀ¼

rem ����ǰ�ļ����е�����Э���ļ�ת��Ϊcpp�ļ�
for %%i in (*.proto) do (  
echo %%i
protoc.exe  --cpp_out=../cpp %%i
)
echo end
pause