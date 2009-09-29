
#include <Implementations/SimpleObjectController.h>

#include <IObjectDrivers.h>

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

    connect( driver, SIGNAL( message( ObjectInputMessage* ) ), 
             this,     SLOT( inputMessage( ObjectInputMessage* ) ) );

    connect( this,    SIGNAL( outputMessage( ObjectOutputMessage* ) ), 
             this,     SLOT( message( ObjectOutputMessage* ) ) );

    return true; 
};

//-------------------------------------------------------

void SimpleObjectController::message( CoreObjectMessage* )
{
    return;
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

