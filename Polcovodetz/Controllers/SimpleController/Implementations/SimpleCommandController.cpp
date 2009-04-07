
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

    connect( inDriver, SIGNAL( message( CommandInputMessage* ) ), 
             this,     SLOT( inputMessage( CommandInputMessage* ) ) );

    connect( this,    SIGNAL( outputMessage( CommandOutputMessage* ) ), 
             this,     SLOT( message( CommandOutputMessage* ) ) );

    return true; 
};

//-------------------------------------------------------
/**
    В сущности, все действия должны приниматься здесь.
*/
void SimpleCommandController::inputMessage( CommandInputMessage* /*mesage*/ )
{
    return;
}

//-------------------------------------------------------

