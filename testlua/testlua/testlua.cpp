// testlua.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LuaManager.h"
#include "pbc.h"
#include "sproto.h"


#pragma comment(lib, "libprotobuf.lib")  
#pragma comment(lib, "libprotoc.lib")  

//#include "person.pb.h"


static void read_file (const char *filename , struct pbc_slice *slice) {
		FILE *f = fopen(filename, "rb");
		if (f == NULL) {
			slice->buffer = NULL;
			slice->len = 0;
			return;
		}
		fseek(f,0,SEEK_END);
		slice->len = ftell(f);
		fseek(f,0,SEEK_SET);
		slice->buffer = malloc(slice->len);
		if (fread(slice->buffer, 1 , slice->len , f) == 0)
			exit(1);
		fclose(f);
}

static void read_file (const char *filename , char *& buffer,int &len) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		buffer = NULL;
		len = 0;
		return;
	}
	fseek(f,0,SEEK_END);
	len = ftell(f);
	fseek(f,0,SEEK_SET);
	buffer = (char *)malloc(len);
	if (fread(buffer, 1 ,len , f) == 0)
		exit(1);
	fclose(f);
}

void testSproto()
{
	char * szBuffer = NULL;
	int len = 0;
	read_file("../../protoc-gen-lua/protoc-gen-lua/example/sproto/person.sproto",szBuffer,len);

	if (szBuffer && len)
	{
		//读取
		struct sproto * p = sproto_create(szBuffer, len);
		if (p)
		{

		}

	}
}
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
//	bRet = LuaManager::shareLuaManager()->DoLuaString
		//("package.path = package.path ..';../../protoc-gen-lua/protoc-gen-lua/example/?.lua;../../protoc-gen-lua/protoc-gen-lua/protobuf/?.lua'");
	bRet = LuaManager::shareLuaManager()->DoLuaString
		("package.path = package.path ..';../../protoc-gen-lua/protoc-gen-lua/example/pbc/?.lua;../../protoc-gen-lua/protoc-gen-lua/example/pbc/?.lua'");
	//bRet = LuaManager::shareLuaManager()->DoLuaString("print(package.path)");
	//bRet = LuaManager::shareLuaManager()->callLuaFuncPar("../../protoc-gen-lua/protoc-gen-lua/example/test.lua","testpb",in,out);

	//解析testpbc
	//Person person;
	//person.ParseFromString(szText);

	//printf("person id = %d ,name = %s,email = %s",person.id(),person.name().c_str(),person.email().c_str());


	//解析testpbc message
	CParamGroup out2;
	_ParamData * pData2 = new _ParamData();
	char szText2[128] = {0};
	pData2->SetParam(szText2,"string",128);
	out2.Push(pData2);
	bRet = LuaManager::shareLuaManager()->DoLuaString("local a = package.loadlib(\"lpeg.dll\", \"luaopen_lpeg\"); a()");
	bRet = LuaManager::shareLuaManager()->DoLuaString("local a = package.loadlib(\"protobuf.dll\", \"luaopen_protobuf_c\"); a()");
	bRet = LuaManager::shareLuaManager()->callLuaFuncPar("../../protoc-gen-lua/protoc-gen-lua/example/pbc/pbctest.lua","testpbc1",in,out2);

	struct pbc_slice slice;
	read_file("person.pb", &slice);
	if (slice.buffer == NULL)	return 1;
	struct pbc_env * env = pbc_new();
	int r = pbc_register(env, &slice);
	if (r) {
		printf("Error : %s", pbc_error(env));
		return 1;
	}
	free(slice.buffer);
	slice.buffer = szText2; slice.len = strlen(szText2);
	struct pbc_rmessage * m = pbc_rmessage_new(env, "Person", &slice);
	if (m==NULL) {
		printf("Error : %s",pbc_error(env));
		return -1;
	}
	printf("name = %s\n", pbc_rmessage_string(m , "name" , 0 , NULL));
	printf("id = %d\n", pbc_rmessage_integer(m , "id" , 0 , NULL));
	printf("email = %s\n", pbc_rmessage_string(m , "email" , 0 , NULL));



	//pattern

	bRet = LuaManager::shareLuaManager()->callLuaFuncPar("../../protoc-gen-lua/protoc-gen-lua/example/pbc/pbctest.lua","testpbc2",in,out);
	//对应proto格式
	struct person {
		int32_t id;
		struct pbc_slice name;	//字符串
		struct pbc_slice email;	//字符串
	};
	struct pbc_slice slice2;
	read_file("person.pb", &slice2);
	if (slice2.buffer == NULL)
		return 1;
	struct pbc_env * env2 = pbc_new();
	pbc_register(env2, &slice2);

	free(slice2.buffer);
	static struct pbc_pattern *pat = pbc_pattern_new(env2, "Person" , 
		"id %d name %s email %s",offsetof(struct person, id) , offsetof(struct person, name) ,offsetof(struct person, email));

	char buffer[4096];
	struct pbc_slice message = { buffer, sizeof(buffer) };

	strcpy((char*)message.buffer,szText);
	message.len = strlen(szText);
	struct person p;

	int n = pbc_pattern_unpack(pat, &message, &p);
	if (n>=0) {
		char text[100] = {0};
		strncpy(text,(const char *)p.name.buffer,p.name.len);
		printf("name = %s\n",text);
		printf("id = %d\n",p.id);
		printf("email = %s\n",(const char *)p.email.buffer);

		pbc_pattern_close_arrays(pat,&p);
	}

	pbc_pattern_delete(pat);

	pbc_delete(env2);


	//解析sproto
	bRet = LuaManager::shareLuaManager()->DoLuaString
		("package.path = package.path ..';../../protoc-gen-lua/protoc-gen-lua/example/sproto/?.lua'");

	CParamGroup out3;
	unsigned char str[200] ={0};
	_ParamData *pData3 = new _ParamData();
	pData3->SetParam(str,"string",200);
	out3.Push(pData3);

	int len = 0;

	_ParamData *pData4 = new _ParamData();
	pData4->SetParam(&len,"int",sizeof(int));
	out3.Push(pData4);

	//bRet = LuaManager::shareLuaManager()->DoLuaString("local a = package.loadlib(\"sproto.dll\", \"luaopen_sproto_core\"); a()");
	bRet = LuaManager::shareLuaManager()->callLuaFuncPar("../../protoc-gen-lua/protoc-gen-lua/example/sproto/sprototest.lua","testsproto",in,out3);

	//printf("%-----len:%d",str,len);

	//for(int i = 0; i < len; ++i)
	//{
	//	printf("%02X\n",str[i]);
	//}

	//struct sproto *proto =  sproto_create(str,len);
	//取值
	CParamGroup out4;

	_ParamData *pData5 = new _ParamData();
	pData5->SetParam(str,"string",len);
	in.Push(pData5);

	bRet = LuaManager::shareLuaManager()->callLuaFuncPar("../../protoc-gen-lua/protoc-gen-lua/example/sproto/sprototest.lua","sprotodecode",in,out4);


	//testSproto();

	system("pause");


	return 0;
}

