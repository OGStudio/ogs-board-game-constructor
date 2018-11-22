FEATURE main.h/Setup
this->kvc->registerKey(
    "application.nodePool.createSphere",
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

            // Create sphere.
            auto pool = this->app->nodePool;
            auto name = values[0];
            auto radius = atof(values[1].c_str());
            pool->createSphere(name, radius);
        }

        return std::vector<std::string>();
    )
);
