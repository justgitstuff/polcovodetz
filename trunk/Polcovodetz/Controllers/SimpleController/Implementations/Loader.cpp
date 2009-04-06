
#include <Implementations/Loader.h>
#include <Implementations/SimpleCommandController.h>

#include <QVector>

//-------------------------------------------------------

struct LoaderImpl
{
    QVector< IAbstractController* > outControllers;
};

//-------------------------------------------------------

Loader::Loader()
{
    m_impl.reset( new LoaderImpl() );
}

//-------------------------------------------------------

Loader::~Loader()
{
    foreach( IAbstractController* controller, m_impl->outControllers )
        delete controller;
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
    return 0; 
};

//-------------------------------------------------------

IObjectController* Loader::getObjectController()
{ 
    return 0; 
};

//-------------------------------------------------------

