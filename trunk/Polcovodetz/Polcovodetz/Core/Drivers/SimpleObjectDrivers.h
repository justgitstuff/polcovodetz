

#ifndef  __SIMPLE_OBJECT_DRIVERS
#define  __SIMPLE_OBJECT_DRIVERS

//-------------------------------------------------------

#include <Core/PObjects/PObject.h>
#include <IObjectDrivers.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

class IGroupOutputDriver;

//-------------------------------------------------------

/**

*/
class SimpleObjectInputDriver : public IObjectInputDriver
{
    Q_OBJECT;

public:
    SimpleObjectInputDriver(){};

    bool init( const boost::shared_ptr< IObjectController >& );

    bool dConnect( const boost::shared_ptr< IGroupOutputDriver >& );
    
    bool registerKey( int key );
};

//-------------------------------------------------------
/**
 
*/
class SimpleObjectOutputDriver : public IObjectOutputDriver
{
    Q_OBJECT;

public:
    SimpleObjectOutputDriver(){};

    bool init( const boost::shared_ptr< IObjectController >& );

    bool dConnect( const PtrPObject& );
};

//-------------------------------------------------------

#endif //__SIMPLE_OBJECT_DRIVERS

//-------------------------------------------------------

