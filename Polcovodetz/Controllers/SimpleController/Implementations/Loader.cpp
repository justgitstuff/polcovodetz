
#include <Implementations/Loader.h>

#include <Implementations/SimpleCommandController.h>
#include <Implementations/SimpleGroupController.h>
#include <Implementations/SimpleObjectController.h>

#include <QVector>

//-------------------------------------------------------

struct LoaderImpl
{
};

//-------------------------------------------------------

Loader::Loader()
{
    m_impl.reset( new LoaderImpl() );
}

//-------------------------------------------------------

Loader::~Loader()
{
}

//-------------------------------------------------------

QString Loader::name()const
{ 
    return "SimpleLoader"; 
};

//-------------------------------------------------------

QString Loader::description()const
{ 
    return "SimpleLoader"; 
};

//-------------------------------------------------------

ICommandController* Loader::getCommandController()
{ 
    return new SimpleCommandController(); 
};

//-------------------------------------------------------

IGroupController* Loader::getGroupController()
{ 
    return new SimpleGroupController(); 
};

//-------------------------------------------------------

IObjectController* Loader::getObjectController()
{ 
    return new SimpleObjectController(); 
};

//-------------------------------------------------------

