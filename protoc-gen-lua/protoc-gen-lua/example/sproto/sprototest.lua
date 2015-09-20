--[[local a = package.loadlib("sproto.dll", "luaopen_sproto_core"); 
a()]]

local sproto = require "sproto"
local print_r = require "print_r"
require "string"

--关闭
function testsproto( )
	-- body
	local  file = io.open("person.sproto","r");
	local  buf = file:read("*a");
	file:close();

	print(buf);

	local sp = sproto.parse(buf);

	print(type(sp));

	--默认值
	local def = sp:default "Person"
	print("default table for Person")
	print_r(def)
	print("--------------")

	local ab = {
	    person = {
	        {
	            name = "Alice",
	            id = 10000,
	            phone = {
	                { number = "123456789" , type = 1 },
	                { number = "87654321" , type = 2 },
	            }
	        },
	        {
	            name = "Bob",
	            id = 20000,
	            phone = {
	                { number = "01234567890" , type = 3 },
	            }
	        }
	    }
	}


	local code = sp:encode("AddressBook", ab)
	return code,string.len(code);
end

--解析--
function sprotodecode(bytes)
	local  file = io.open("person.sproto","r");
	local  buf = file:read("*a");
	file:close();

	print(buf);

	local sp = sproto.parse(buf);
	local addr = sp:decode("AddressBook", bytes);
	print_r(addr);
end
