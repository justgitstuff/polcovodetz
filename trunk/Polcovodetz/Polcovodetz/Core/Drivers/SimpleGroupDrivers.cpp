
//-------------------------------------------------------

#include <Core/Drivers/SimpleGroupDrivers.h>

//-------------------------------------------------------

bool SimpleGroupInputDriver::init( const boost::shared_ptr< IGroupController >&/* cc */)
{
    return true;
}

//-------------------------------------------------------

bool SimpleGroupOutputDriver::init( const boost::shared_ptr< IGroupController >&/* cc */)
{
    return true;
}

//-------------------------------------------------------

bool SimpleGroupInputDriver::dConnect( const boost::shared_ptr< ICommandOutputDriver >& )
{
    return true;
}

//-------------------------------------------------------

bool SimpleGroupOutputDriver::dConnect( const boost::shared_ptr< IObjectInputDriver >& )
{
    return true;
}

//-------------------------------------------------------

