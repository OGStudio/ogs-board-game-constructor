FEATURE api.lua/Impl
function main.application.nodePool.createSphere(self, name, radius)
    local key = "application.nodePool.createSphere"
    ENV:call(key, {name, radius})
    return scene.createNode(name)
end
