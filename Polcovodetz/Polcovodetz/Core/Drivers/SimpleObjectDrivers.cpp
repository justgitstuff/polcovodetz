
//-------------------------------------------------------

#include <Core/Drivers/SimpleObjectDrivers.h>

#include <Core/BaseClasses/IObjectController.h>
#include <Core/Calculations/DriverHelper.h>
#include <Core/Calculations/MapOperations.h>
#include <Core/MultiThreading/CommandState.h>
#include <Core/PolkApp.h>

#include <QSize>

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

PtrPObject SimpleObjectDriver::ptrPObject()const
{
    return m_impl->connectedObject;
}

//-------------------------------------------------------

void SimpleObjectDriver::setSpeed( const int persent )
{
    m_impl->state->setSpeed( ptrPObject(), QPoint( persent, 0 ) );
}

//-------------------------------------------------------

void SimpleObjectDriver::setRotation( const ObjectRotation& rotation )
{
    switch( rotation )
    {
    case ToTop :
        m_impl->state->setRotation( ptrPObject(), 0 );
        break;

    case ToRight :
        m_impl->state->setRotation( ptrPObject(), 90 );
        break;

    case ToBottom:
        m_impl->state->setRotation( ptrPObject(), 180 );
        break;

    case ToLeft :
        m_impl->state->setRotation( ptrPObject(), 270 );
        break;
    }
}

//-------------------------------------------------------

void SimpleObjectDriver::setRotation( const MovementDirection& rotation )
{
    switch( rotation.direction() )
    {
    case MovementDirection::Down :
        return setRotation( ::ToBottom );
    case MovementDirection::Top :
        return setRotation( ::ToTop );
    case MovementDirection::Left :
        return setRotation( ::ToLeft );
    case MovementDirection::Right :
        return setRotation( ::ToRight );
    }
}

//-------------------------------------------------------

void SimpleObjectDriver::makeAttack()
{
    PtrPObject who = m_impl->connectedObject;

    m_impl->state->makeRocket( who );
}

//-------------------------------------------------------

MovementDirection SimpleObjectDriver::nearestPointToFlag()const
{
    QPoint flag = m_impl->mapOperations->flagPoint( 3 - m_impl->state->side() );

    return nearestPointTo( flag );
}

//-------------------------------------------------------

MovementDirection SimpleObjectDriver::nearestPointTo( const QPoint& squareNumber )const
{
    QPoint position = m_impl->connectedObject->position();

    position /= PolkApp::SQUARE_SIZE;

    return m_impl->mapOperations->nearestPointFromPath( position, squareNumber );
}

//-------------------------------------------------------

void SimpleObjectDriver::message( CoreObjectMessage* msg )
{
    if( m_impl->controller.get() != 0 )
        m_impl->controller->message( msg );
}

//-------------------------------------------------------

void SimpleObjectDriver::message( GroupObjectMessage* msg )
{
    if( m_impl->controller.get() != 0 )
        m_impl->controller->message( msg );
}

//-------------------------------------------------------

void SimpleObjectDriver::message( CommandObjectMessage* msg )
{
    if( m_impl->controller.get() != 0 )
        m_impl->controller->message( msg );
}

//-------------------------------------------------------

MovementDirection SimpleObjectDriver::getRandomRotation()const
{
    static int base = MovementDirection::Down;

    base += 90;
    base %= 360;

    return MovementDirection( base );
}

//-------------------------------------------------------

QPoint SimpleObjectDriver::convertToNumber( const QPoint& bigCoordinates )const
{
    return bigCoordinates / PolkApp::SQUARE_SIZE; 
}

//-------------------------------------------------------

QPoint SimpleObjectDriver::convertToCoordinate( const QPoint& squareNumber )const
{
    return squareNumber * PolkApp::SQUARE_SIZE; 
}

//-------------------------------------------------------

