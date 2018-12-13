FEATURE scene.h/Impl
private:
    render::VBO
    void setupRoot()
    {
        auto root = new osg::MatrixTransform;
        this->nodes["root"] = root;
    }
