FEATURE main.h/Setup
this->kvc->registerKey(
    "application.resourcePool.resource.exists",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        // Set.
        if (!values.empty())
        {
            // Make sure there are two components.
            if (values.size() != 2)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 2"
                );
                return std::vector<std::string>();
            }

            // Locate named resource.
            auto pool = this->app->resourcePool;
            auto group = values[0];
            auto name = values[1];
            auto res = pool->resource(group, name);
            // Report its presence.
            if (res != 0)
            {
                return std::vector<std::string>({ "true" });
            }
        }

        return std::vector<std::string>();
    )
);
