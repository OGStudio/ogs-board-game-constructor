FEATURE main.h/Setup
this->setupKVC();

FEATURE main.h/TearDown
this->tearKVCDown();

FEATURE main.h/Impl
private:
    script::KVC *kvc;
    void setupKVC()
    {
        this->kvc = new script::KVC(this->environment);
    }
    void tearKVCDown()
    {
        delete this->kvc;
    }
