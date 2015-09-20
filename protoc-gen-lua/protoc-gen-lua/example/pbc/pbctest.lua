--包含test
require "protobuf"
local pa = require "parser" -- 解析

function testpbc1()
	-- body
	--读取pb文件
	local  file = io.open("person.pb","rb");
	local  buf = file:read("*a");		--读取全部文件
	file:close();

	protobuf.register(buf);


	local  person = 
	{
		id = 101,
		name = "test";
		email = "test@163.com"
	}

	--data--序列化和反序列化
	local data = protobuf.encode("Person",person);
	--local t = protobuf.decode("Person",data);
	--print(t.id,t.name,t.email);
	print(type(data));
	return data;
end



function  testpbc2()
	-- body
	--利用parse解析
	--文件名/路径
	--proto文件
	local parsedata = pa.register("person.proto",".")

	local data = protobuf.pack("Person id name email",110,"test2","test2@qq.com");

	print(type(data));
	return data;
	--print(data);

	--解析proto,返回每一个选项,且根据前面的定义来，好像sscanf
	--print(protobuf.unpack("Person name id email",data));
end



