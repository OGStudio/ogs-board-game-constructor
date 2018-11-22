FEATURE main.h/Include
#include <fstream>

FEATURE main.h/Setup
this->loadLocalIndexScript();

FEATURE main.h/Impl
private:
    void loadLocalIndexScript()
    {
        // Make sure `base` parameter exists.
        auto it = this->parameters.find("base");
        if (it == this->parameters.end())
        {
            MAIN_EXAMPLE_LOG(
                "WARNING Not loading `index.lua` "
                "because `base` parameter is missing"
            );
            return;
        }

        auto base = it->second;
        auto path = base + "/index.lua";
        MAIN_EXAMPLE_LOG("Loading a script from '%s'", path.c_str());
        std::ifstream localScript(path);
        if (localScript)
        {
            // Read file contents into string.
            std::string fileContents(
                (std::istreambuf_iterator<char>(localScript)),
                (std::istreambuf_iterator<char>())
            );
            this->executeScript(fileContents);
        }
        else
        {
            MAIN_EXAMPLE_LOG("ERROR Could not read the script");
        }
    }
