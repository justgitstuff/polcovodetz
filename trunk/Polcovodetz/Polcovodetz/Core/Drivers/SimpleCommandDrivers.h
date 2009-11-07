

#ifndef  __SIMPLE_COMMAND_DRIVERS
#define  __SIMPLE_COMMAND_DRIVERS

//-------------------------------------------------------

#include <ICommandDrivers.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

class CommandState;
class IGroupDriver;

struct SimpleCommandInputDriverImpl;
struct SimpleCommandOutputDriverImpl;

//-------------------------------------------------------

/**
 Драйвер для соединения ICommandController
 и PolkApp
*/
class SimpleCommandInputDriver : public ICommandInputDriver
{
    Q_OBJECT;

public:
    SimpleCommandInputDriver();

    bool init( const boost::shared_ptr< ICommandController >&, CommandState& );

    void sendMessage( CoreCommandMessage* );
    void sendMessage( GroupCommandMessage* );

    bool registerKey( Qt::Key key );

private:
    boost::shared_ptr< SimpleCommandInputDriverImpl > m_impl;
};

//-------------------------------------------------------
/**
 Драйвер для соединения ICommandController
 и его подчиненных. 
*/
class SimpleCommandOutputDriver : public ICommandOutputDriver
{
    Q_OBJECT;

public:
    SimpleCommandOutputDriver( CommandState* );
    ~SimpleCommandOutputDriver(){};

    bool init();

    bool dConnect( const boost::shared_ptr< IGroupDriver >& );

    void createObjectForDriver( const qint64 driverID, const int objectRTTI );

private slots:

private:
    boost::shared_ptr< SimpleCommandOutputDriverImpl > m_impl;

};

//-------------------------------------------------------

#endif //__SIMPLE_COMMAND_DRIVERS

//-------------------------------------------------------

