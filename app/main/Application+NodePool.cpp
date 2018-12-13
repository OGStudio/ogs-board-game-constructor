FEATURE main.h/Setup
this->setupNodePool();

FEATURE main.h/TearDown
this->tearNodePoolDown();

FEATURE main.h/Impl
public:
    NodePool *nodePool;
private:
    void setupNodePool()
    {
        this->nodePool = new NodePool;

        // Set pool's root node to viewer.
        auto root = this->nodePool->node("root");
        this->setScene(root);
    }
    void tearNodePoolDown()
    {
        this->setScene(0);
        delete this->nodePool;
    }
