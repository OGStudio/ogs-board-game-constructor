FEATURE main.h/Setup
this->kvc->registerKey(
    "application.nodePool.createNode",
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

            // Create node.
            auto pool = this->app->nodePool;
            auto name = values[0];
            pool->createNode(name);
        }

        return std::vector<std::string>();
    )
);
