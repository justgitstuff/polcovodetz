
//-------------------------------------------------------

#include <Core/Drivers/SimpleObjectDrivers.h>

//-------------------------------------------------------

bool SimpleObjectInputDriver::init( const boost::shared_ptr< IObjectController >&/* cc */)
{
    return true;
}

//-------------------------------------------------------

bool SimpleObjectOutputDriver::init( const boost::shared_ptr< IObjectController >& /*cc */)
{
    return true;
}

//-------------------------------------------------------

bool SimpleObjectInputDriver::dConnect( const boost::shared_ptr< IGroupOutputDriver >& )
{
    return true;
}

//-------------------------------------------------------

bool SimpleObjectOutputDriver::dConnect( const PtrPObject& )
{
    return true;
}

//-------------------------------------------------------

bool SimpleObjectInputDriver::registerKey( int /*key */)
{
    return false;
}

//-------------------------------------------------------

