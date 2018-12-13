FEATURE main.h/Impl
private:
    render::VBOSetupVisitor vbo;

FEATURE main.h/Node
node->accept(this->vbo);
