FEATURE api.lua/Start
-- NOTE This is only a wrapper for a valid material at C++ side.
-- NOTE This does NOT create anything at C++ side.
function render.createMaterial(name)
    local instance = {
        __name = name,

FEATURE api.lua/End
    }
    return instance
end
