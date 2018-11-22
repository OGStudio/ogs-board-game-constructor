FEATURE api.lua/Impl
function main.application.nodePool.createNode(self, name)
    local key = "application.nodePool.createNode"
    ENV:call(key, {name})
    return scene.createNode(name)
end
