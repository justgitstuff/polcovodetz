
#include <Implementations/SimpleObjectController.h>

#include <IObjectDrivers.h>
#include <Messages.h>
#include <MovementDirection.h>

#include <QDebug>

//-------------------------------------------------------

struct SimpleObjectControllerImpl
{
    IObjectDriver*  driver;
};

//-------------------------------------------------------

SimpleObjectController::SimpleObjectController()
:IObjectController()
{
    m_impl.reset( new SimpleObjectControllerImpl() );
}

//-------------------------------------------------------
/**
    Имя контролера
*/
QString SimpleObjectController::name()const
{ 
    return "SimpleObjectController"; 
};

//-------------------------------------------------------
/**
    Краткое описание.

    Данное поле, возможно, будет работать через интерниционализацию, а, потому,
    на данный момент является временным.
*/
QString SimpleObjectController::description()const
{ 
    return QString::fromLocal8Bit( "Простейшая реализация интерфейса IObjectController" ); 
};

//-------------------------------------------------------
/**
    Здесь будет полезнным сохранить указатели на классы IObjectDriver
    и IObjectDriver. 

    Напомним, что ядро ( PolkApp ) гарантирует, что драйвера удаляются ПОСЛЕ
    каждого раунда игры, причем, необходимое условие: к драйверу не подсоединен
    ни один объект.
*/
bool SimpleObjectController::init( IObjectDriver* driver )
{
    m_impl->driver  = driver;

    return true; 
};

//-------------------------------------------------------

void SimpleObjectController::message( CoreObjectMessage* message )
{
    switch( message->type )
    {
    case CoreObjectMessage::Recreated :
        {
            m_impl->driver->setSpeed( 100 );

            MovementDirection md = m_impl->driver->nearesPointToFlag();

            m_impl->driver->setRotation( md );

            break;
        }
    case CoreObjectMessage::SquareChanged :
        {
            MovementDirection md = m_impl->driver->nearesPointToFlag();

            m_impl->driver->setRotation( md );

            m_impl->driver->makeAttack();

            break;
        }
    case CoreObjectMessage::Staying:
        {
            MovementDirection md = m_impl->driver->getRandomRotation();

            m_impl->driver->setRotation( md );

            m_impl->driver->makeAttack();

            break;
        }
    }
}

//-------------------------------------------------------
/**
    В сущности, все действия должны приниматься здесь.
*/
//void SimpleObjectController::inputMessage( ObjectInputMessage* /*mesage*/ )
//{
//    return;
//}

//-------------------------------------------------------

