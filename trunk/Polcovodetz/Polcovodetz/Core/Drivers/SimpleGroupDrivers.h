

#ifndef  __SIMPLE_GROUP_DRIVERS
#define  __SIMPLE_GROUP_DRIVERS

//-------------------------------------------------------

#include <IGroupDrivers.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

class IObjectInputDriver;
class ICommandOutputDriver;

//-------------------------------------------------------

/**
 Драйвер для соединения IGroupController
 и ICommandController
*/
class SimpleGroupInputDriver : public IGroupInputDriver
{
    Q_OBJECT;

public:
    SimpleGroupInputDriver(){};

    bool init( const boost::shared_ptr< IGroupController >& );

    bool dConnect( const boost::shared_ptr< ICommandOutputDriver >& );

    bool registerKey( Qt::Key );
};

//-------------------------------------------------------
/**
 Драйвер для соединения IGroupController
 и его подчиненных. 
*/
class SimpleGroupOutputDriver : public IGroupOutputDriver
{
    Q_OBJECT;

public:
    SimpleGroupOutputDriver(){};

    bool init( const boost::shared_ptr< IGroupController >& );

    bool dConnect( const boost::shared_ptr< IObjectInputDriver >& );
};

//-------------------------------------------------------

#endif //__SIMPLE_GROUP_DRIVERS

//-------------------------------------------------------

