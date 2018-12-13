FEATURE main.h/Setup
this->kvc->registerKey(
    "application.materialPool.material.setShaders",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        // Set.
        if (!values.empty())
        {
            // Make sure there are 5 components.
            if (values.size() != 5)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 5",
                    key.c_str()
                );
                return std::vector<std::string>();
            }

            auto materialName = values[0];
            auto vertexShaderGroup = values[1];
            auto vertexShaderName = values[2];
            auto fragmentShaderGroup = values[3];
            auto fragmentShaderName = values[4];

            // Locate material.
            auto material = this->app->materialPool->material(materialName);
            // Locate shaders.
            auto vertexShader =
                this->app->resourcePool->resource(
                    vertexShaderGroup,
                    vertexShaderName
                );
            auto fragmentShader =
                this->app->resourcePool->resource(
                    fragmentShaderGroup,
                    fragmentShaderName
                );

            // Make sure material and shaders exist.
            if (
                !material ||
                !vertexShader ||
                !fragmentShader
            ) {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set vertex shader '%s/%s' and fragment "
                    "shader '%s/%s' for material '%s' "
                    "because material and/or shader(s) do(es) not exist",
                    vertexShaderGroup.c_str(),
                    vertexShaderName.c_str(),
                    fragmentShaderGroup.c_str(),
                    fragmentShaderName.c_str(),
                    materialName.c_str()
                );
                return std::vector<std::string>();
            }

            // Apply shaders to material.
            auto prog =
                render::createShaderProgram(
                    vertexShader->contents,
                    fragmentShader->contents
                );
            material->setAttribute(prog);
        }

        return std::vector<std::string>();
    )
);
