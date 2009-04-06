

#ifndef  __LOADER
#define  __LOADER

//-------------------------------------------------------

#include <ILoader.h>

//-------------------------------------------------------

class Loader : public ILoader
{
public:
    Loader();

    virtual QString             name()const;
    virtual QString             description()const;

    virtual ICommandController* getCommandController();
    virtual IGroupController*   getGroupController();
    virtual IObjectController*  getObjectController();


};

//-------------------------------------------------------

#endif //__LOADER

//-------------------------------------------------------

