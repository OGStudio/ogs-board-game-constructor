FEATURE api.lua/Methods
main.application.camera = {

FEATURE api.lua/Properties
}

-- Set metatable to have properties easily.
local cameraMT = core.createPropertiesMT()
setmetatable(main.application.camera, cameraMT)
