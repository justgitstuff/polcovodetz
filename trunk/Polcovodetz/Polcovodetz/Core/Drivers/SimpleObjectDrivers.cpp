
//-------------------------------------------------------

#include <Core/Drivers/SimpleObjectDrivers.h>

#include <Core/BaseClasses/IObjectController.h>

#include <Core/MultiThreading/CommandThread.h>
#include <Core/PolkApp.h>

//-------------------------------------------------------

struct SimpleObjectInputDriverImpl
{

    boost::shared_ptr< IObjectController > controller;
};

//-------------------------------------------------------

struct SimpleObjectOutputDriverImpl
{
    SimpleObjectOutputDriverImpl():connectedObject(){}

    PtrPObject                             connectedObject;

    CommandThread*                         thread;
};

//-------------------------------------------------------

SimpleObjectInputDriver::SimpleObjectInputDriver()
:IObjectInputDriver(), m_impl( new SimpleObjectInputDriverImpl())
{
}

//-------------------------------------------------------

SimpleObjectInputDriver::~SimpleObjectInputDriver()
{
}

//-------------------------------------------------------

bool SimpleObjectInputDriver::init( const boost::shared_ptr< IObjectController >& oc )
{
    m_impl->controller = oc;
    return true;
}

//-------------------------------------------------------

bool SimpleObjectOutputDriver::init( const boost::shared_ptr< IObjectController >& /*oc */)
{
    return true;
}

//-------------------------------------------------------

bool SimpleObjectInputDriver::dConnect( const boost::shared_ptr< IGroupOutputDriver >& )
{
    return true;
}

//-------------------------------------------------------

bool SimpleObjectInputDriver::registerKey( Qt::Key key )
{
    return pApp.registerKey( key, this );
}

//-------------------------------------------------------

void SimpleObjectInputDriver::processKey( Qt::Key key )
{
    if( m_impl->controller->wantListenKeys() )
        m_impl->controller->keyPressed( key );
}

//-------------------------------------------------------

SimpleObjectOutputDriver::SimpleObjectOutputDriver( CommandThread* thread )
:m_impl( new SimpleObjectOutputDriverImpl() )
{
    m_impl->thread = thread;
}

//-------------------------------------------------------

bool SimpleObjectOutputDriver::dConnect( const PtrPObject& object )
{
    m_impl->connectedObject = object;
    return true;
}

//-------------------------------------------------------

PtrPObject& SimpleObjectOutputDriver::pObject()
{
    return m_impl->connectedObject;
}

//-------------------------------------------------------

void SimpleObjectOutputDriver::setSpeed( const int persent )
{
    m_impl->thread->setSpeed( pObject(), QPoint( persent, 0 ) );
}

//-------------------------------------------------------

void SimpleObjectOutputDriver::setRotation( const ObjectRotation& rotation )
{
    switch( rotation )
    {
    case ToTop :
        m_impl->thread->setRotation( pObject(), 0 );
        break;

    case ToRight :
        m_impl->thread->setRotation( pObject(), 90 );
        break;

    case ToBottom:
        m_impl->thread->setRotation( pObject(), 180 );
        break;

    case ToLeft :
        m_impl->thread->setRotation( pObject(), 270 );
        break;
    }
}

//-------------------------------------------------------

