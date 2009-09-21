
#include <Implementations/SimpleCommandController.h>

#include <ICommandDrivers.h>
#include <Messages.h>

#include <QDebug>

//-------------------------------------------------------

struct SimpleCommandControllerImpl
{
    ICommandInputDriver*  inDriver;
    ICommandOutputDriver* outDriver;
};

//-------------------------------------------------------

SimpleCommandController::SimpleCommandController()
:ICommandController()
{
    m_impl.reset( new SimpleCommandControllerImpl() );
}

//-------------------------------------------------------
/**
    Имя контролера
*/
QString SimpleCommandController::name()const
{ 
    return "SimpleCommandController"; 
};

//-------------------------------------------------------
/**
    Краткое описание.

    Данное поле, возможно, будет работать через интерниционализацию, а, потому,
    на данный момент является временным.
*/
QString SimpleCommandController::description()const
{ 
    return QString::fromLocal8Bit( "Простейшая реализация интерфейса ICommandController" ); 
};

//-------------------------------------------------------
/**
    Здесь будет полезнным сохранить указатели на классы ICommandInputDriver
    и ICommandOutputDriver. 

    Напомним, что ядро ( PolkApp ) гарантирует, что драйвера удаляются ПОСЛЕ
    каждого раунда игры, причем, необходимое условие: к драйверу не подсоединен
    ни один объект.
*/
bool SimpleCommandController::init( ICommandInputDriver* inDriver , ICommandOutputDriver* outDriver )
{
    m_impl->inDriver  = inDriver;
    m_impl->outDriver = outDriver;
/*
    connect( inDriver,  SIGNAL( message( CoreCommandMessage* ) ), 
             this,      SLOT( message( CoreCommandMessage* ) ) );

    connect( inDriver,  SIGNAL( message( GroupCommandMessage* ) ), 
             this,      SLOT( message( GroupCommandMessage* ) ) );
*/
    return true; 
};

//-------------------------------------------------------
/**
    В сущности, все действия должны приниматься здесь.
*/
void SimpleCommandController::message( CoreCommandMessage* message )
{
    switch( message->type )
    {
    case CoreCommandMessage::GameStarted :
        qDebug( "Game started" );

        break;
    case CoreCommandMessage::ObjectCrached :
        {
            m_impl->outDriver->createObjectForDriver( message->who, message->objectRTTI );

            qDebug( "new object created" );

            break;
        }
    default:
        qDebug( "unknown message" );

        break;
    }

    return;
}

//-------------------------------------------------------
/**
    В сущности, все действия должны приниматься здесь.
*/
void SimpleCommandController::message( GroupCommandMessage* )
{
    return;
}

//-------------------------------------------------------

