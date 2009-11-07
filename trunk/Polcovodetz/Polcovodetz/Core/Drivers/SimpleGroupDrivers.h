

#ifndef  __SIMPLE_GROUP_DRIVERS
#define  __SIMPLE_GROUP_DRIVERS

//-------------------------------------------------------

#include <IGroupDrivers.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

class ICommandOutputDriver;

//-------------------------------------------------------

/**
 Драйвер для соединения IGroupController
 и ICommandController
*/
class SimpleGroupDriver : public IGroupDriver
{
    Q_OBJECT;

public:
    SimpleGroupDriver(){};

    bool init( const boost::shared_ptr< IGroupController >& );

    bool dConnect( const boost::shared_ptr< ICommandOutputDriver >& );

    bool registerKey( Qt::Key );
};

//-------------------------------------------------------

#endif //__SIMPLE_GROUP_DRIVERS

//-------------------------------------------------------

