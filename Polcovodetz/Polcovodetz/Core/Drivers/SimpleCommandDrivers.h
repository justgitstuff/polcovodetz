

#ifndef  __SIMPLE_COMMAND_DRIVERS
#define  __SIMPLE_COMMAND_DRIVERS

//-------------------------------------------------------

#include <ICommandDrivers.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

class CommandThread;
class IGroupInputDriver;

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

    bool init( const boost::shared_ptr< ICommandController >&, CommandThread& );

    void sendMessage( CoreCommandMessage* );
    void sendMessage( GroupCommandMessage* );

    bool registerKey( int key );

signals:
    void message( CoreCommandMessage* );
    void message( GroupCommandMessage* );

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
    SimpleCommandOutputDriver(){};

    bool init( const boost::shared_ptr< ICommandController >& );

    bool dConnect( const boost::shared_ptr< IGroupInputDriver >& );

private slots:

};

//-------------------------------------------------------

#endif //__SIMPLE_COMMAND_DRIVERS

//-------------------------------------------------------

