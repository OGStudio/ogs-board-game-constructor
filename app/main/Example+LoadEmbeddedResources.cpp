FEATURE main.h/Include
#include "shaders/color.vert.h"
#include "shaders/color.frag.h"
#include "resource.h"

FEATURE main.h/Setup
this->loadEmbeddedResources();

FEATURE main.h/Impl
private:
    void loadEmbeddedResources()
    {
        auto resourcePool = this->app->resourcePool;
        resourcePool->addResource(
            resource::Resource(
                "shaders",
                "color.vert",
                color_vert,
                color_vert_len
            )
        );
        resourcePool->addResource(
            resource::Resource(
                "shaders",
                "color.frag",
                color_frag,
                color_frag_len
            )
        );
    }
