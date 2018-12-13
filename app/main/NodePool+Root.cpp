FEATURE main.h/Setup
this->setupRoot();

FEATURE main.h/Impl
private:
    void setupRoot()
    {
        auto root = new osg::MatrixTransform;
        this->nodes["root"] = root;
    }
