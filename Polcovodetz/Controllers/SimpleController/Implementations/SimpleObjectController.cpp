
#include <Implementations/SimpleObjectController.h>

#include <IObjectDrivers.h>
#include <Messages.h>
#include <MovementDirection.h>

#include <QDebug>

//-------------------------------------------------------

enum ObjectState
{
    GoToFlag,
    PatrolSquare
};

//-------------------------------------------------------

struct SimpleObjectControllerImpl
{
    IObjectDriver*    driver;

    QRect             patrolSquare;

    ObjectState       state;

    MovementDirection nextPoint();

    /**
        Номер угла. Требуется для патрулирования.
        По сценарию, объект идет к углам последовательно: 0, 1, 2, 3, 4, 1, 2, ...
    */
    int               squareNumber;

    /**
        Точка, в которую планируется дойти.
    */
    QPoint            plannedPoint;

public:
    inline void       planNextPatrolPoint();

private:

    static inline QPoint nextCorner( int& cornerNum, const QRect& rect );
};

//-------------------------------------------------------

MovementDirection SimpleObjectControllerImpl::nextPoint()
{
    switch( state )
    {
    case ::GoToFlag :
        {
            return driver->nearestPointToFlag();
        }
    case ::PatrolSquare : 
        {
            QPoint square = driver->pObject()->position();            

            if( ( square.x() <= patrolSquare.x() || square.x() >= patrolSquare.x() + patrolSquare.width() ) &&
                ( square.y() <= patrolSquare.y() || square.y() >= patrolSquare.y() + patrolSquare.height() ) )
                planNextPatrolPoint();

            return driver->nearestPointTo( plannedPoint );
        }
    }

    return MovementDirection();
}

//-------------------------------------------------------

void SimpleObjectControllerImpl::planNextPatrolPoint()
{
    plannedPoint = nextCorner( squareNumber, patrolSquare );
}

//-------------------------------------------------------

QPoint SimpleObjectControllerImpl::nextCorner( int& cornerNum, const QRect& rect )
{
    cornerNum++;

    switch( cornerNum % 4 )
    {
    case 0 :
        return rect.topLeft();
    case 1 :
        return rect.topRight();
    case 2 :
        return rect.bottomRight();
    case 3 :
        return rect.bottomLeft();
    default:
        return rect.bottomRight();
    }
}

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

            m_impl->state = ::GoToFlag;

            MovementDirection md = m_impl->driver->nearestPointToFlag();

            m_impl->driver->setRotation( md );

            break;
        }
    case CoreObjectMessage::SquareOutChanged :
        {
            MovementDirection md = m_impl->nextPoint();

            m_impl->driver->setRotation( md );

            m_impl->driver->makeAttack();

            break;
        }
   // case CoreObjectMessage::Blocked:
    case CoreObjectMessage::Staying:
        {
            PtrAPObject obj = m_impl->driver->pObject();

            if( obj == 0 )
                return;

            int rotation = obj->rotation();

            m_impl->driver->setRotation( MovementDirection( ( rotation + 90 ) % 360 ) );

            m_impl->driver->makeAttack();

            break;
        }
    }
}

//-------------------------------------------------------
/**
    В сущности, все действия должны приниматься здесь.
*/
void SimpleObjectController::message( GroupObjectMessage* message )
{
    switch( message->type )
    {
    case GroupObjectMessage::PatrolSquare :
        {
            m_impl->patrolSquare = message->rect;

            m_impl->state = ::PatrolSquare;

            m_impl->planNextPatrolPoint();

            break;
        }
    case GroupObjectMessage::GoToFlag :
        {
            m_impl->state = ::GoToFlag;

            break;
        }
    }

    return;
}

//-------------------------------------------------------

