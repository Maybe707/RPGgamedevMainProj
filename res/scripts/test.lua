local test = {}

function test:init()
	print("Test1.lua: "..self.instance:getNameComponent().name)
end

function test:update(deltaTime)
	-- print(deltaTime.." Test1.lua: "..self.instance:getNameComponent().name)	
end

function test:destroy()
	print("This is destroy from lua")
end

return test

