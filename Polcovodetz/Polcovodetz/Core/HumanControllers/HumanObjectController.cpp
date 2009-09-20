
//-------------------------------------------------------

#include <Core/HumanControllers/HumanObjectController.h>

#include <IObjectDrivers.h>

#include <QDebug>
#include <QKeyEvent>

//-------------------------------------------------------

struct HumanObjectControllerImpl
{
    IObjectInputDriver*  inDriver;
    IObjectOutputDriver* outDriver;
};

//-------------------------------------------------------

HumanObjectController::HumanObjectController()
:IObjectController(), m_impl( new HumanObjectControllerImpl() )
{
}

//-------------------------------------------------------
/**
    Имя контролера
*/
QString HumanObjectController::name()const
{ 
    return "HumanObjectController"; 
};

//-------------------------------------------------------
/**
    Краткое описание.

    Данное поле, возможно, будет работать через интерниционализацию, а, потому,
    на данный момент является временным.
*/
QString HumanObjectController::description()const
{ 
    return QString::fromLocal8Bit( "Простейшая реализация интерфейса IObjectController" ); 
};

//-------------------------------------------------------
/**
    Здесь будет полезнным сохранить указатели на классы IObjectInputDriver
    и IObjectOutputDriver. 

    Напомним, что ядро ( PolkApp ) гарантирует, что драйвера удаляются ПОСЛЕ
    каждого раунда игры, причем, необходимое условие: к драйверу не подсоединен
    ни один объект.
*/
bool HumanObjectController::init( IObjectInputDriver* inDriver , IObjectOutputDriver* outDriver )
{
    m_impl->inDriver  = inDriver;
    m_impl->outDriver = outDriver;

    connect( inDriver, SIGNAL( message( ObjectInputMessage* ) ), 
             this,     SLOT( inputMessage( ObjectInputMessage* ) ) );

    connect( this,    SIGNAL( outputMessage( ObjectOutputMessage* ) ), 
             this,     SLOT( message( ObjectOutputMessage* ) ) );

    inDriver->registerKey( Qt::Key_Left );
    inDriver->registerKey( Qt::Key_Right );
    inDriver->registerKey( Qt::Key_Up );
    inDriver->registerKey( Qt::Key_Down );
    inDriver->registerKey( Qt::Key_Space );

    return true; 
};

//-------------------------------------------------------

void HumanObjectController::keyPressed( const Qt::Key key )
{
    switch( key )
    {
    case Qt::Key_Left :
        {
            qDebug("Left!");

            m_impl->outDriver->setRotation( ToLeft );
            m_impl->outDriver->setSpeed( 100 );

            break;
        }
    case Qt::Key_Right :
        {
            qDebug("Right!");
            
            m_impl->outDriver->setRotation( ToRight );
            m_impl->outDriver->setSpeed( 100 );

            break;
        }
    case Qt::Key_Up :
        {
            qDebug("Up!");
            
            m_impl->outDriver->setRotation( ToTop );
            m_impl->outDriver->setSpeed( 100 );

            break;
        }
    case Qt::Key_Down :
        {
            qDebug("Down!");
            
            m_impl->outDriver->setRotation( ToBottom );
            m_impl->outDriver->setSpeed( 100 );

            break;
        }
    case Qt::Key_Space :
        {
            qDebug("Atack!");

            m_impl->outDriver->makeAttack();
        }
    }
}

//-------------------------------------------------------
/**
    В сущности, все действия должны приниматься здесь.
*/
void HumanObjectController::inputMessage( ObjectInputMessage* /*mesage*/ )
{
    return;
}


//-------------------------------------------------------

