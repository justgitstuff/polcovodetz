

#ifndef  __SIMPLE_COMMAND_DRIVERS
#define  __SIMPLE_COMMAND_DRIVERS

//-------------------------------------------------------

#include <ICommandDrivers.h>

//-------------------------------------------------------

/**
 Драйвер для соединения ICommandController
 и PolkApp
*/
class SimpleCommandInputDriver : public ICommandInputDriver
{
    Q_OBJECT;

public:
    SimpleCommandInputDriver(){};

signals:
    /**
        Сигнал приема сообщений.
    */
    void message( CommandInputMessage* mesage );
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

public slots:

    /**
      Слот для принятия сообщений
    */
    virtual void message( const CommandOutputMessage& ){};
};

//-------------------------------------------------------

#endif //__SIMPLE_COMMAND_DRIVERS

//-------------------------------------------------------

