FEATURE main.h/Setup
this->kvc->registerKey(
    "application.materialPool.createMaterial",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        // Set.
        if (!values.empty())
        {
            // Make sure there is one component.
            if (values.size() != 1)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 1"
                );
                return std::vector<std::string>();
            }

            // Create material.
            auto pool = this->app->materialPool;
            auto name = values[0];
            pool->createMaterial(name);
        }

        return std::vector<std::string>();
    )
);
