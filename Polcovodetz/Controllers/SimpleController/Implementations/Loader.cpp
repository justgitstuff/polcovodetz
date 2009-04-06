
#include <Implementations/Loader.h>
#include <Implementations/SimpleCommandController.h>

//-------------------------------------------------------

Loader::Loader()
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
    return 0; 
};

//-------------------------------------------------------

IObjectController* Loader::getObjectController()
{ 
    return 0; 
};

//-------------------------------------------------------

