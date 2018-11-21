FEATURE main.h/Include
#include "network.h"

FEATURE main.h/Setup
this->loadIndexScript();

FEATURE main.h/Impl
private:
    void loadIndexScript()
    {
        // Make sure `base` parameter exists.
        auto it = this->parameters.find("base");
        if (it == this->parameters.end())
        {
            return;
        }

        auto base = it->second;
        auto path = base + "/index.lua";
        MAIN_EXAMPLE_LOG("Loading a script from '%s'", path.c_str());

        auto success = [&](std::string response) {
            MAIN_EXAMPLE_LOG("Successfully loaded the script");
            this->executeScript(response);
        };
        auto failure = [&](std::string reason) {
            MAIN_EXAMPLE_LOG(
                "ERROR Could not load the script. '%s'",
                reason.c_str()
            );
        };
        // GET.
        this->app->httpClient->get(path, success, failure);
    }
