
//-------------------------------------------------------

#include <Core/Drivers/SimpleGroupDrivers.h>

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

