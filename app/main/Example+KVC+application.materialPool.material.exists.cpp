FEATURE main.h/Setup
this->kvc->registerKey(
    "application.materialPool.material.exists",
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

            // Locate named material.
            auto pool = this->app->materialPool;
            auto name = values[0];
            auto material = pool->material(name);
            // Report its presence.
            if (material != 0)
            {
                return std::vector<std::string>({ "true" });
            }
        }

        return std::vector<std::string>();
    )
);
