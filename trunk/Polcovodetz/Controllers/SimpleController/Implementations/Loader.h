

#ifndef  __LOADER
#define  __LOADER

//-------------------------------------------------------

#include <ILoader.h>

#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct LoaderImpl;

//-------------------------------------------------------

class Loader : public ILoader
{
public:
            Loader();

    virtual ~Loader();

    virtual QString             name()const;
    virtual QString             description()const;

    virtual ICommandController* getCommandController();
    virtual IGroupController*   getGroupController();
    virtual IObjectController*  getObjectController();

private:
    boost::shared_ptr< LoaderImpl > m_impl;

};

//-------------------------------------------------------

#endif //__LOADER

//-------------------------------------------------------

