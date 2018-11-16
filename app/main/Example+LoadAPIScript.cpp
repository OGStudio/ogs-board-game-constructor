FEATURE main.h/Include
#include "api.lua.h"
#include "resource.h"

FEATURE main.h/Setup
this->loadAPIScript();

FEATURE main.h/Impl
private:
    void loadAPIScript()
    {
        MAIN_EXAMPLE_LOG("Loading embedded API script");
        resource::Resource apiRes(
            "scripts",
            "api.lua",
            api_lua,
            api_lua_len
        );
        // Execute the script.
        try {
            this->lua->script(apiRes.contents);
            MAIN_EXAMPLE_LOG("Successfully loaded embedded API script");
        }
        catch (const std::exception &e)
        {
            MAIN_EXAMPLE_LOG(
                "ERROR Could not load embedded API script. %s",
                e.what()
            );
        }
    }
