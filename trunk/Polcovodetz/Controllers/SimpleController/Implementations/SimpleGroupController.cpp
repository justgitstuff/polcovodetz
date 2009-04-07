
#include <Implementations/SimpleGroupController.h>

#include <IGroupDrivers.h>

//-------------------------------------------------------

struct SimpleGroupControllerImpl
{
    IGroupInputDriver*  inDriver;
    IGroupOutputDriver* outDriver;
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
bool SimpleGroupController::init( IGroupInputDriver* inDriver , IGroupOutputDriver* outDriver )
{
    m_impl->inDriver  = inDriver;
    m_impl->outDriver = outDriver;

    connect( inDriver, SIGNAL( message( GroupInputMessage* ) ), 
             this,     SLOT( inputMessage( GroupInputMessage* ) ) );

    connect( this,    SIGNAL( outputMessage( GroupOutputMessage* ) ), 
             this,     SLOT( message( GroupOutputMessage* ) ) );

    return true; 
};

//-------------------------------------------------------
/**
    В сущности, все действия должны приниматься здесь.
*/
void SimpleGroupController::inputMessage( GroupInputMessage* /*mesage*/ )
{
    return;
}

//-------------------------------------------------------

