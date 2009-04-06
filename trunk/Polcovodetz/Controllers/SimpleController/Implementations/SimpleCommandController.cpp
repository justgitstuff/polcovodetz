
#include <Implementations/SimpleCommandController.h>

#include <ICommandDrivers.h>

//-------------------------------------------------------

SimpleCommandController::SimpleCommandController()
{
}

//-------------------------------------------------------

QString SimpleCommandController::name()const
{ 
    return "abc"; 
};

//-------------------------------------------------------

QString SimpleCommandController::description()const
{ 
    return "abc"; 
};

//-------------------------------------------------------

bool SimpleCommandController::init( ICommandInputDriver*, ICommandOutputDriver* )
{
    return false; 
};

//-------------------------------------------------------

