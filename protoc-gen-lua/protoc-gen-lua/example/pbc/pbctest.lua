--包含test
require "protobuf"

--读取pb文件
local  file = io.open("../pb/person.pb","rb");
local  buf = file:read("&*a");		--读取全部文件
file:close();

protobuf.register(buf);


local  person = 
{
	id = 101,
	name = "test";
	email = "test@163.com"
}

--data
local data = protobuf.encode("Person",person);
local t = protobuf.decode("Person",data);

for k,v in pairs(t) do
	if type(k) == "string" then
		print(k,v)
	end
end

print(t.id,t.name,t.email);
