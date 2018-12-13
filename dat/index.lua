-- Get shortcuts.
local materialPool = main.application.materialPool
local nodePool = main.application.nodePool
local resourcePool = main.application.resourcePool

-- Create scene.
local sphere = nodePool:createSphere("sphere", 1)
local root = nodePool:node("root")
root:addChild(sphere)

-- Create simple material for the whole scene.
local mat = materialPool:createMaterial("color")
mat:setShaders(
    resourcePool:resource("shaders", "color.vert"),
    resourcePool:resource("shaders", "color.frag")
)
mat:setUniform("color", {1, 0, 0})
root:setMaterial(mat)


