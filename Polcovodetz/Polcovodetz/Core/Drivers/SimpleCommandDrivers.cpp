
//-------------------------------------------------------

#include <Core/Drivers/SimpleCommandDrivers.h>

#include <Core/BaseClasses/ICommandController.h>

#include <Core/MultiThreading/CommandState.h>

//-------------------------------------------------------

struct SimpleCommandInputDriverImpl
{   
    boost::shared_ptr< ICommandController > cc;
    CommandState* cState;
};

//-------------------------------------------------------

struct SimpleCommandOutputDriverImpl
{   
    CommandState* cState;
};

//-------------------------------------------------------

SimpleCommandInputDriver::SimpleCommandInputDriver()
{
    m_impl.reset( new SimpleCommandInputDriverImpl() );
}

//-------------------------------------------------------

bool SimpleCommandInputDriver::init( const boost::shared_ptr< ICommandController >& cc, CommandState& cState )
{
    m_impl->cc = cc;
    m_impl->cState = &cState;

    return true;
}

//-------------------------------------------------------

void SimpleCommandInputDriver::sendMessage( CoreCommandMessage* msg )
{
    m_impl->cc->message( msg );

    return;
}

//-------------------------------------------------------

void SimpleCommandInputDriver::sendMessage( GroupCommandMessage* )
{
    return;
}

//-------------------------------------------------------

SimpleCommandOutputDriver::SimpleCommandOutputDriver( CommandState* cState )
:m_impl( new SimpleCommandOutputDriverImpl() )
{
    m_impl->cState = cState;
}

//-------------------------------------------------------

bool SimpleCommandOutputDriver::init()
{
    return true;
}

//-------------------------------------------------------

bool SimpleCommandOutputDriver::dConnect( const boost::shared_ptr< IGroupInputDriver >& )
{
    return true;
}

//-------------------------------------------------------

void SimpleCommandOutputDriver::createObjectForDriver( const qint64 driverID, const int objectRTTI )
{
    m_impl->cState->createConnectedObject( objectRTTI, driverID );
    //m_impl->cState
}

//-------------------------------------------------------

bool SimpleCommandInputDriver::registerKey( Qt::Key /*key */)
{
    return false;
}

//-------------------------------------------------------

