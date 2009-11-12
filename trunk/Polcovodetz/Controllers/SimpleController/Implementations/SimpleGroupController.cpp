
#include <Implementations/SimpleGroupController.h>

#include <IGroupDrivers.h>

//-------------------------------------------------------

struct SimpleGroupControllerImpl
{
    IGroupDriver*  driver;
};

//-------------------------------------------------------

SimpleGroupController::SimpleGroupController()
:IGroupController()
{
    m_impl.reset( new SimpleGroupControllerImpl() );
}

//-------------------------------------------------------
/**
    Имя контролера
*/
QString SimpleGroupController::name()const
{ 
    return "SimpleGroupController"; 
};

//-------------------------------------------------------
/**
    Краткое описание.

    Данное поле, возможно, будет работать через интерниционализацию, а, потому,
    на данный момент является временным.
*/
QString SimpleGroupController::description()const
{ 
    return QString::fromLocal8Bit( "Простейшая реализация интерфейса IGroupController" ); 
};

//-------------------------------------------------------
/**
    Здесь будет полезнным сохранить указатели на классы IGroupInputDriver
    и IGroupOutputDriver. 

    Напомним, что ядро ( PolkApp ) гарантирует, что драйвера удаляются ПОСЛЕ
    каждого раунда игры, причем, необходимое условие: к драйверу не подсоединен
    ни один объект.
*/
bool SimpleGroupController::init( IGroupDriver* driver )
{
    m_impl->driver  = driver;

    return true; 
};

/**
   Прием сообщений от главнокоммандующего.
*/
void SimpleGroupController::message( CommandGroupMessage* mes )
{
    switch( mes->type )
    {
    case CommandGroupMessage::Attack :
        {
            break;
        }
    case CommandGroupMessage::FlagProtection :
        {
            break;
        }
    }
}

//-------------------------------------------------------

