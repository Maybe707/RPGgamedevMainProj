local test2 = { }

function test2:init()
	print("Test2.lua: "..self.instance:getNameComponent().name)	
end

return test2
