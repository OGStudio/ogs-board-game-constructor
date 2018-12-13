FEATURE api.lua/Impl
function main.application.materialPool.createMaterial(self, name)
    local key = "application.materialPool.createMaterial"
    ENV:call(key, {name})
    return render.createMaterial(name)
end
