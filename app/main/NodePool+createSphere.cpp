FEATURE main.h/Start
public:
    osg::MatrixTransform *createSphere(
        const std::string &name,
        float radius
    ) {
        auto node = scene::createSphere(radius);
        node->setName(name);
        this->nodes[name] = node;

FEATURE main.h/End
        return node;
    }
