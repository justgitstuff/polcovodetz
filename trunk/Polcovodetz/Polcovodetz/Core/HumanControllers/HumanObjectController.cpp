
//-------------------------------------------------------

#include <Core/HumanControllers/HumanObjectController.h>

#include <IObjectDrivers.h>

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

    return true; 
};

//-------------------------------------------------------
/**
    В сущности, все действия должны приниматься здесь.
*/
void HumanObjectController::inputMessage( ObjectInputMessage* /*mesage*/ )
{
    return;
}


//-------------------------------------------------------

