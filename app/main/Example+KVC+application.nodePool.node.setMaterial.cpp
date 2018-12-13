FEATURE main.h/Setup
this->kvc->registerKey(
    "application.nodePool.node.setMaterial",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        // Set.
        if (!values.empty())
        {
            // Make sure there is at least one component.
            if (values.size() < 1)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is less than 1",
                    key.c_str()
                );
                return std::vector<std::string>();
            }

            // Locate named node.
            auto nodeName = values[0];
            auto node = this->app->nodePool->node(nodeName);

            // Locate material if it was specified.
            std::string materialName = "(nil)";
            osg::StateSet *material = 0;
            if (values.size() == 2)
            {
                materialName = values[1];
                material = this->app->materialPool->material(materialName);
            }

            // Make sure node exists.
            if (!node)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set material '%s' for node '%s' "
                    "because node does not exist",
                    materialName.c_str(),
                    nodeName.c_str()
                );
                return std::vector<std::string>();
            }

            // Apply material.
            node->setStateSet(material);
        }

        return std::vector<std::string>();
    )
);
