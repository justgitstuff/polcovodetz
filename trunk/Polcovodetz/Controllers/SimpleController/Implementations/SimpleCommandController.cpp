
#include <Implementations/SimpleCommandController.h>

#include <ICommandDrivers.h>

//-------------------------------------------------------

struct SimpleCommandControllerImpl
{
    ICommandInputDriver*  inDriver;
    ICommandOutputDriver* outDriver;
};

//-------------------------------------------------------

SimpleCommandController::SimpleCommandController()
{
    m_impl.reset( new SimpleCommandControllerImpl() );
}

//-------------------------------------------------------

QString SimpleCommandController::name()const
{ 
    return "SimpleCommandController"; 
};

//-------------------------------------------------------

QString SimpleCommandController::description()const
{ 
    return "Простейшая реализация интерфейса"; 
};

//-------------------------------------------------------
/**
    Здесь будет полезнным сохранить указатели на классы ICommandInputDriver
    и ICommandOutputDriver. 

    Напомним, что ядро ( PolkApp ) гарантирует, что драйвера удаляются ПОСЛЕ
    каждого раунда игры, причем, необходимое условие: к драйверу не подсоединен
    ни один объект.
*/

bool SimpleCommandController::init( ICommandInputDriver*, ICommandOutputDriver* )
{
    return false; 
};

//-------------------------------------------------------

