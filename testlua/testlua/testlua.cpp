// testlua.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LuaManager.h"


#pragma comment(lib, "libprotobuf.lib")  
#pragma comment(lib, "libprotoc.lib")  

#include "person.pb.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CParamGroup in;
	CParamGroup out;

	_ParamData * pData = new _ParamData();
	char szText[128] = {0};
	pData->SetParam(szText,"string",128);
	out.Push(pData);

	bool bRet = false;
	//bRet = LuaManager::shareLuaManager()->DoLuaString("package.path = package.path ..';F:/u3d/proto-lua/protoc-gen-lua/protoc-gen-lua/example/?.lua;F:/u3d/proto-lua/protoc-gen-lua/protoc-gen-lua/protobuf/?.lua'");
	bRet = LuaManager::shareLuaManager()->DoLuaString
		("package.path = package.path ..';../../protoc-gen-lua/protoc-gen-lua/example/?.lua;../../protoc-gen-lua/protoc-gen-lua/protobuf/?.lua'");
	//bRet = LuaManager::shareLuaManager()->DoLuaString("print(package.path)");
	bRet = LuaManager::shareLuaManager()->callLuaFuncPar("../../protoc-gen-lua/protoc-gen-lua/example/test.lua","testpbc",in,out);

	//½âÎötestpbc
	Person person;
	person.ParseFromString(szText);

	printf("person id = %d ,name = %s,email = %s",person.id(),person.name().c_str(),person.email().c_str());

	system("pause");


	return 0;
}

