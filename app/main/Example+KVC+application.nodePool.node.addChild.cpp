FEATURE main.h/Setup
this->kvc->registerKey(
    "application.nodePool.node.addChild",
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

            auto pool = this->app->nodePool;
            auto parentName = values[0];
            auto childName = values[1];
            auto parent = pool->node(parentName);
            auto child = pool->node(childName);

            // Make sure parent and child exist.
            if (!parent || !child)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not add '%s' child node to '%s' parent node "
                    "because node(s) do(es) not exist",
                    childName.c_str(),
                    parentName.c_str()
                );
                return std::vector<std::string>();
            }

            parent->addChild(child);
        }

        return std::vector<std::string>();
    )
);
