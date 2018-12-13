FEATURE main.h/Include
#include "scene.h"
#include <osg/MatrixTransform>

FEATURE main.h/Setup
class NodePool
{
    public:
        NodePool()
        {

FEATURE main.h/TearDown
        }
        ~NodePool()
        {

FEATURE main.h/Impl
        }

    private:
        std::map<std::string, osg::ref_ptr<osg::MatrixTransform> > nodes;

FEATURE main.h/End
};
