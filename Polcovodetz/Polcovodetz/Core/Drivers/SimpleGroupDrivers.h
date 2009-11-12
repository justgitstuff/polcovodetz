

#ifndef  __SIMPLE_GROUP_DRIVERS
#define  __SIMPLE_GROUP_DRIVERS

//-------------------------------------------------------

#include <IGroupDrivers.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

class ICommandOutputDriver;
class CommandState;

class GroupObjectMessage;

struct SimpleGroupDriverImpl;

//-------------------------------------------------------

/**
 Драйвер для соединения IGroupController
 и ICommandController
*/
class SimpleGroupDriver : public IGroupDriver
{
    Q_OBJECT;

public:
    SimpleGroupDriver( CommandState* );

    bool init( const boost::shared_ptr< IGroupController >& );

    bool dConnect( const boost::shared_ptr< ICommandOutputDriver >& );

    bool registerKey( Qt::Key );

    
    void sendObjectMessage( GroupObjectMessage* );

private:
    boost::shared_ptr< SimpleGroupDriverImpl > m_impl;
};

//-------------------------------------------------------

#endif //__SIMPLE_GROUP_DRIVERS

//-------------------------------------------------------

