
//-------------------------------------------------------

#include <Core/Drivers/SimpleObjectDrivers.h>

#include <Core/BaseClasses/IObjectController.h>
#include <Core/Calculations/DriverHelper.h>
#include <Core/Calculations/MapOperations.h>
#include <Core/MultiThreading/CommandState.h>
#include <Core/PolkApp.h>

//-------------------------------------------------------

struct SimpleObjectDriverImpl
{
    SimpleObjectDriverImpl():connectedObject(){}

    boost::shared_ptr< IObjectController > controller;
    CommandState*                          state;
    MapOperations*                         mapOperations;

    PtrPObject                             connectedObject;
};


//-------------------------------------------------------

SimpleObjectDriver::SimpleObjectDriver( CommandState* state )
:IObjectDriver(), m_impl( new SimpleObjectDriverImpl())
{
    m_impl->state = state;

    m_impl->mapOperations = state->driverHelper()->mapOperations();
}

//-------------------------------------------------------

SimpleObjectDriver::~SimpleObjectDriver()
{
}

//-------------------------------------------------------

bool SimpleObjectDriver::init( const boost::shared_ptr< IObjectController >& oc )
{
    m_impl->controller = oc;

    return true;
}

//-------------------------------------------------------

bool SimpleObjectDriver::oConnect( const PtrPObject& object )
{
    m_impl->connectedObject = object;

    return true;
}

//-------------------------------------------------------

bool SimpleObjectDriver::registerKey( Qt::Key key )
{
    return pApp.registerKey( key, this );
}

//-------------------------------------------------------

void SimpleObjectDriver::processKey( Qt::Key key )
{
    if( m_impl->controller->wantListenKeys() )
        m_impl->controller->keyPressed( key );
}

//-------------------------------------------------------

PtrPObject& SimpleObjectDriver::pObject()
{
    return m_impl->connectedObject;
}

//-------------------------------------------------------

void SimpleObjectDriver::setSpeed( const int persent )
{
    m_impl->state->setSpeed( pObject(), QPoint( persent, 0 ) );
}

//-------------------------------------------------------

void SimpleObjectDriver::setRotation( const ObjectRotation& rotation )
{
    switch( rotation )
    {
    case ToTop :
        m_impl->state->setRotation( pObject(), 0 );
        break;

    case ToRight :
        m_impl->state->setRotation( pObject(), 90 );
        break;

    case ToBottom:
        m_impl->state->setRotation( pObject(), 180 );
        break;

    case ToLeft :
        m_impl->state->setRotation( pObject(), 270 );
        break;
    }
}

//-------------------------------------------------------

void SimpleObjectDriver::makeAttack()
{
    PtrPObject who = m_impl->connectedObject;

    m_impl->state->makeRocket( who );
}

//-------------------------------------------------------

MovementDirection SimpleObjectDriver::nearesPointToFlag()const
{
    QPoint flag = m_impl->mapOperations->flagPoint( m_impl->state->side() );

    QPoint position = m_impl->connectedObject->position();

    position /= PolkApp::SQUARE_SIZE;

    return m_impl->mapOperations->nearestPointFromPath( position, flag );
}

//-------------------------------------------------------

