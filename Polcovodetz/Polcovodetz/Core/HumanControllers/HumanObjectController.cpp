
//-------------------------------------------------------

#include <Core/HumanControllers/HumanObjectController.h>

#include <IObjectDrivers.h>

#include <QDebug>
#include <QKeyEvent>

//-------------------------------------------------------

struct HumanObjectControllerImpl
{
    IObjectDriver*  driver;
};

//-------------------------------------------------------

HumanObjectController::HumanObjectController()
:IObjectController(), m_impl( new HumanObjectControllerImpl() )
{
}

//-------------------------------------------------------
/**
    ��� ����������
*/
QString HumanObjectController::name()const
{ 
    return "HumanObjectController"; 
};

//-------------------------------------------------------
/**
    ������� ��������.

    ������ ����, ��������, ����� �������� ����� �������������������, �, ������,
    �� ������ ������ �������� ���������.
*/
QString HumanObjectController::description()const
{ 
    return QString::fromLocal8Bit( "���������� ���������� ���������� IObjectController" ); 
};

//-------------------------------------------------------
/**
    ����� ����� ��������� ��������� ��������� �� ������ IObjectDriver
    � IObjectDriver. 

    ��������, ��� ���� ( PolkApp ) �����������, ��� �������� ��������� �����
    ������� ������ ����, ������, ����������� �������: � �������� �� �����������
    �� ���� ������.
*/
bool HumanObjectController::init( IObjectDriver* driver )
{
    m_impl->driver  = driver;

    driver->registerKey( Qt::Key_Left );
    driver->registerKey( Qt::Key_Right );
    driver->registerKey( Qt::Key_Up );
    driver->registerKey( Qt::Key_Down );
    driver->registerKey( Qt::Key_Space );

    return true; 
};

//-------------------------------------------------------

void HumanObjectController::keyPressed( const Qt::Key key )
{
    switch( key )
    {
    case Qt::Key_Left :
        {
            m_impl->driver->setRotation( ToLeft );
            m_impl->driver->setSpeed( 100 );

            break;
        }
    case Qt::Key_Right :
        {
            m_impl->driver->setRotation( ToRight );
            m_impl->driver->setSpeed( 100 );

            break;
        }
    case Qt::Key_Up :
        {            
            m_impl->driver->setRotation( ToTop );
            m_impl->driver->setSpeed( 100 );

            break;
        }
    case Qt::Key_Down :
        {
            m_impl->driver->setRotation( ToBottom );
            m_impl->driver->setSpeed( 100 );

            break;
        }
    case Qt::Key_Space :
        {
            m_impl->driver->makeAttack();

            break;
        }
    }
}

//-------------------------------------------------------
/**
    � ��������, ��� �������� ������ ����������� �����.
*/
void HumanObjectController::message( GroupObjectMessage* /*mesage*/ )
{
    return;
}


//-------------------------------------------------------

