
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
-- core.Reporter Start
-- NOTE This is a core::Reporter (C++) implementation in Lua.
function core.createReporter()
    local instance = {
        -- Internal list of callbacks.
        __callbacks = {},

        -- Add a new callback.
        addCallback = function(self, callback, name)
            -- Work around callback reactivation happenning
            -- before `report()` call.
            if (self:__reactivateInactiveCallback(name))
            then
                return
            end
            local item = {
                callback = callback,
                name = name
            }
            table.insert(self.__callbacks, item)
        end,

        -- Internal list of one-time callbacks.
        __oneTimeCallbacks = {},

        -- Add a callback that is only executed once.
        addOneTimeCallback = function(self, callback)
            table.insert(self.__oneTimeCallbacks, callback)
        end,

        -- Internal list of callback names to remove later.
        __inactiveCallbackNames = {},

        removeCallback = function(self, name)
            -- This call only deactivates a callback for
            -- later removal that happens during next report() call.
            for _, callback in pairs(self.__callbacks)
            do
                if 
                    callback.name and
                    (callback.name == name)
                then
                    table.insert(self.__inactiveCallbackNames, name)
                end
            end
        end,

        report = function(self)
            self:__removeInactiveCallbacks()
            
            -- Call normal callbacks.
            for _, callback in pairs(self.__callbacks)
            do
                callback.callback()
            end

            -- Create a copy of the list of one-time callbacks.
            local oneTimeCallbacks = {table.unpack(self.__oneTimeCallbacks)}
            -- Remove one-time callbacks.
            self.__oneTimeCallbacks = {}
            -- Call one-time callbacks.
            for _, callback in pairs(oneTimeCallbacks)
            do
                callback()
            end
        end,

        __reactivateInactiveCallback = function(self, name)
            for id, callbackName in pairs(self.__inactiveCallbackNames)
            do
                if (callbackName == name)
                then
                    self.__inactiveCallbackNames[id] = nil
                    return true
                end
            end
            return false
        end,

        __removeInactiveCallbacks = function(self)
            -- Loop through the names of inactive callbacks.
            for _, name in pairs(self.__inactiveCallbackNames)
            do
                -- Loop through callbacks to find matching name.
                for id, callback in pairs(self.__callbacks)
                do
                    if 
                        callback.name and
                        (callback.name == name)
                    then
                        -- Remove matching callback.
                        self.__callbacks[id] = nil
                        break
                    end
                end
            end
            -- Clear the list of the names of inactive callbacks.
            self.__inactiveCallbackNames = {}
        end,
    }
    return instance
end
-- core.Reporter End

render = {}

-- render.Material Start
-- NOTE This is only a wrapper for a valid material at C++ side.
-- NOTE This does NOT create anything at C++ side.
function render.createMaterial(name)
    local instance = {
        __name = name,

-- render.Material End
        -- render.Material.setShaders Start
        setShaders = function(self, vertex, fragment)
            local key = "application.materialPool.material.setShaders"
            ENV:call(
                key,
                {
                    self.__name,
                    vertex.__group,
                    vertex.__name,
                    fragment.__group,
                    fragment.__name
                }
            )
        end,
        -- render.Material.setShaders End
        -- render.Material.setUniform Start
        setUniform = function(self, name, rawValue)
            local key = "application.materialPool.material.setUniform"
            local params = {self.__name, name}
            -- Array.
            if (type(rawValue) == "table")
            then
                for _, value in pairs(rawValue)
                do
                    table.insert(params, value)
                end
            -- Single value.
            else
                table.insert(params, rawValue)
            end
        
            ENV:call(key, params)
        end,
        -- render.Material.setUniform End
-- render.Material Start
    }
    return instance
end
-- render.Material End


resource = {}

-- resource.Resource Start
-- NOTE This is only a wrapper for a resource at C++ side.
-- NOTE This does NOT create anything at C++ side.
function resource.createResource(group, name)
    local instance = {
        __group = group,
        __name = name,

-- resource.Resource End
-- resource.Resource Start
    }
    return instance
end
-- resource.Resource End

scene = {}

-- scene.Node Start
-- NOTE This is only a wrapper for a valid node at C++ side.
-- NOTE This does NOT create anything at C++ side.
function scene.createNode(name)
    local instance = {
        __name = name,

-- scene.Node End
        -- scene.Node.addChild Start
        addChild = function(self, node)
            local key = "application.nodePool.node.addChild"
            local parent = self.__name
            local child = node.__name
            ENV:call(key, {parent, child})
        end,
        -- scene.Node.addChild End
        -- scene.Node.setMaterial Start
        setMaterial = function(self, material)
            local key = "application.nodePool.node.setMaterial"
            local node = self.__name
            local params = {node}
            -- If material does not exist, it's a nil material.
            if (material)
            then
                table.insert(params, material.__name)
            end
            ENV:call(key, params)
        end,
        -- scene.Node.setMaterial End
-- scene.Node Start
    }

    -- Set metatable to have properties easily.
    local propertiesMT = core.createPropertiesMT()
    setmetatable(instance, propertiesMT)

-- scene.Node End
    -- scene.Node.position Start
    do
        local shortKey = "position"
        local key = "application.nodePool.node." .. shortKey
        propertiesMT:register(
            shortKey,
            function(self)
                local node = self.__name
                return ENV:call(key, {node})
            end,
            function(self, position)
                local node = self.__name
                ENV:call(
                    key,
                    {
                        node,
                        position[1],
                        position[2],
                        position[3],
                    }
                )
            end
        )
    end
    -- scene.Node.position End
    -- scene.Node.rotation Start
    do
        local shortKey = "rotation"
        local key = "application.nodePool.node." .. shortKey
        propertiesMT:register(
            shortKey,
            function(self)
                local node = self.__name
                return ENV:call(key, {node})
            end,
            function(self, rotation)
                local node = self.__name
                ENV:call(
                    key,
                    {
                        node,
                        rotation[1],
                        rotation[2],
                        rotation[3],
                    }
                )
            end
        )
    end
    -- scene.Node.rotation End
-- scene.Node Start
    return instance
end
-- scene.Node End

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
    -- main.application.camera.position Start
    do
        local shortKey = "position"
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
    -- main.application.camera.position End
    -- main.application.camera.rotation Start
    do
        local shortKey = "rotation"
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
    -- main.application.camera.rotation End

-- main.application.materialPool Start
main.application.materialPool = {}
-- main.application.materialPool End
-- main.application.materialPool.createMaterial Start
function main.application.materialPool.createMaterial(self, name)
    local key = "application.materialPool.createMaterial"
    ENV:call(key, {name})
    return render.createMaterial(name)
end
-- main.application.materialPool.createMaterial End
-- main.application.mouse Start
-- Create mouse.
main.application.mouse = {
    position = {},
    positionChanged = core.createReporter(),

    pressedButtons = {},
    pressedButtonsChanged = core.createReporter(),
}

-- Configure mouse.
do
    local mouse = main.application.mouse
    -- Create environment client.
    local client = EnvironmentClient.new()
    -- Define keys.
    local buttonsKey = "application.mouse.pressedButtons"
    local positionKey = "application.mouse.position"
    -- Define callback.
    client.call = function(key, values)
        if (key == buttonsKey)
        then
            mouse.pressedButtons = values
            mouse.pressedButtonsChanged:report()
        elseif (key == positionKey)
        then
            mouse.position = values
            mouse.positionChanged:report()
        end

        return {}
    end
    -- Register client.
    mouse.client = client
    ENV:addClient(
        mouse.client,
        {
            buttonsKey,
            positionKey
        }
    );
end
-- main.application.mouse End
-- main.application.nodePool Start
main.application.nodePool = {}
-- main.application.nodePool End
-- main.application.nodePool.createNode Start
function main.application.nodePool.createNode(self, name)
    local key = "application.nodePool.createNode"
    ENV:call(key, {name})
    return scene.createNode(name)
end
-- main.application.nodePool.createNode End
-- main.application.nodePool.createSphere Start
function main.application.nodePool.createSphere(self, name, radius)
    local key = "application.nodePool.createSphere"
    ENV:call(key, {name, radius})
    return scene.createNode(name)
end
-- main.application.nodePool.createSphere End
-- main.application.nodePool.node Start
function main.application.nodePool.node(self, name)
    local key = "application.nodePool.node.exists"
    -- Find out if node exists in C++.
    local result = ENV:call(key, {name})
    -- Return nothing if node does not exist.
    if (not result[1]) then
        return nil
    end
    -- Return Lua node representation if node exists in C++.
    return scene.createNode(name)
end
-- main.application.nodePool.node End
-- main.application.resourcePool Start
main.application.resourcePool = { }
-- main.application.resourcePool End
-- main.application.resourcePool.resource Start
function main.application.resourcePool.resource(self, group, name)
    local key = "application.resourcePool.resource.exists"
    -- Find out if resource exists in C++.
    local result = ENV:call(key, {group, name})
    -- Return nothing if resource does not exist.
    if (not result[1]) then
        return nil
    end
    -- Return Lua representation.
    return resource.createResource(group, name)
end
-- main.application.resourcePool.resource End
