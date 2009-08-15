
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
    ����� ����� ��������� ��������� ��������� �� ������ IObjectInputDriver
    � IObjectOutputDriver. 

    ��������, ��� ���� ( PolkApp ) �����������, ��� �������� ��������� �����
    ������� ������ ����, ������, ����������� �������: � �������� �� �����������
    �� ���� ������.
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
    � ��������, ��� �������� ������ ����������� �����.
*/
void HumanObjectController::inputMessage( ObjectInputMessage* /*mesage*/ )
{
    return;
}


//-------------------------------------------------------

