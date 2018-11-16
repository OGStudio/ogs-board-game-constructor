
--[[
This file is part of OGS Board game constructor:
  https://github.com/OGStudio/ogs-board-game-constructor

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
--]]

core = {}

-- core.PropertiesMT Start
function core.createPropertiesMT()
    local instance = {
        -- Register properties with callbacks.
        __callbacks = {},
        register = function(mtself, key, getter, setter)
            local callback = {}
            callback.getter = getter
            callback.setter = setter
            mtself.__callbacks[key] = callback
        end,

        -- Getter.
        __index = function(self, key)
            local mtself = getmetatable(self)
            local callback = mtself.__callbacks[key]
            if 
                callback and
                callback.getter
            then
                return callback.getter(self)
            end
            return nil
        end,

        -- Setter.
        __newindex = function(self, key, value)
            local mtself = getmetatable(self)
            local callback = mtself.__callbacks[key]
            if 
                callback and
                callback.setter
            then
                callback.setter(self, value)
            end
        end,
    }
    return instance
end
-- core.PropertiesMT End

render = {}



resource = {}


scene = {}


main = {}
main.application = {}


-- main.application.camera Start
main.application.camera = {

-- main.application.camera End
-- main.application.camera Start
}

-- Set metatable to have properties easily.
local cameraMT = core.createPropertiesMT()
setmetatable(main.application.camera, cameraMT)
-- main.application.camera End
    -- main.application.camera.clearColor Start
    do
        local shortKey = "clearColor"
        local key = "application.camera." .. shortKey
        cameraMT:register(
            shortKey,
            function(self)
                return ENV:call(key, {})
            end,
            function(self, value)
                ENV:call(key, value)
            end
        )
    end
    -- main.application.camera.clearColor End


-- TODO set bg as a test?
main.application.camera.clearColor = {0, 1, 0}
