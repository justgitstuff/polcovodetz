
//-------------------------------------------------------

#include <Core/Drivers/SimpleCommandDrivers.h>

#include <Core/MultiThreading/CommandThread.h>

//-------------------------------------------------------

struct SimpleCommandInputDriverImpl
{   
    boost::shared_ptr< ICommandController > cc;
    CommandThread* cThread;
};

//-------------------------------------------------------

SimpleCommandInputDriver::SimpleCommandInputDriver()
{
    m_impl.reset( new SimpleCommandInputDriverImpl() );
}

//-------------------------------------------------------

bool SimpleCommandInputDriver::init( const boost::shared_ptr< ICommandController >& cc, CommandThread& cThread )
{
    m_impl->cc = cc;
    m_impl->cThread = &cThread;

//    connect( this, SIGNAL( message( CommandInputMessage* ) ), cc.get(), SLOT( 
    return true;
}

//-------------------------------------------------------

void SimpleCommandInputDriver::sendMessage( CoreCommandMessage* msg )
{
    emit message( msg );

    return;
}

//-------------------------------------------------------

void SimpleCommandInputDriver::sendMessage( GroupCommandMessage* )
{
    return;
}

//-------------------------------------------------------

bool SimpleCommandOutputDriver::init( const boost::shared_ptr< ICommandController >&/* cc */)
{
    return true;
}

//-------------------------------------------------------

bool SimpleCommandOutputDriver::dConnect( const boost::shared_ptr< IGroupInputDriver >& )
{
    return true;
}

//-------------------------------------------------------

