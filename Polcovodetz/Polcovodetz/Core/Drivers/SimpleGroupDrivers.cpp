
//-------------------------------------------------------

#include <Core/Drivers/SimpleGroupDrivers.h>

#include <Core/MultiThreading/CommandState.h>

#include <Messages.h>

//-------------------------------------------------------

struct SimpleGroupDriverImpl
{
    CommandState* command;
};

//-------------------------------------------------------

SimpleGroupDriver::SimpleGroupDriver(  CommandState* command )
:m_impl( new SimpleGroupDriverImpl() )
{
    m_impl->command = command;
}

//-------------------------------------------------------

bool SimpleGroupDriver::init( const boost::shared_ptr< IGroupController >&/* cc */)
{
    return true;
}

//-------------------------------------------------------

bool SimpleGroupDriver::dConnect( const boost::shared_ptr< ICommandOutputDriver >& )
{
    return true;
}

//-------------------------------------------------------

bool SimpleGroupDriver::registerKey( Qt::Key /*key */)
{
    return false;
}

//-------------------------------------------------------

void SimpleGroupDriver::sendObjectMessage( GroupObjectMessage* message )
{
    if( message->id() != -1 )
    {
        m_impl->command->sendMessage( boost::shared_ptr< AbstractMessage >( message ) );
    }
    else
    {
        
    }

}

//-------------------------------------------------------

