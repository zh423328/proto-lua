package.path = package.path .. ';../protobuf/?.lua'

--加载dll,可以在C++直接调用，而不需要写在程序里面
local a = package.loadlib("pb.dll", "luaopen_pb");  
a()

require 'lua/person_pb'

function testpbc()
	-- body
	local person= person_pb.Person()
	person.id = 1000
	person.name = "Alice"
	person.email = "Alice@example.com"

	local data = person:SerializeToString()

	--local msg = person_pb.Person()

	--msg:ParseFromString(data)

	--print(msg)
	return data;
end

