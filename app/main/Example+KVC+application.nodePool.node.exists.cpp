FEATURE main.h/Setup
this->kvc->registerKey(
    "application.nodePool.node.exists",
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

            // Locate named node.
            auto pool = this->app->nodePool;
            auto name = values[0];
            auto node = pool->node(name);
            // Report its presence.
            if (node != 0)
            {
                return std::vector<std::string>({ "true" });
            }
        }

        return std::vector<std::string>();
    )
);
