

#ifndef  __ICOMMAND_DRIVERS
#define  __ICOMMAND_DRIVERS

//-------------------------------------------------------

#include <QObject>

//-------------------------------------------------------

class ICommandController;

//-------------------------------------------------------
/**
  Сообщение, посылаемое к ICommandController
*/
struct CommandInputMessage
{
    CommandInputMessage(){};
};

//-------------------------------------------------------
/**
 Драйвер для соединения ICommandController
 и PolkApp
*/
class ICommandInputDriver : public QObject
{
    Q_OBJECT;

signals:
    /**
        Сигнал приема сообщений.
    */

    void message( CommandInputMessage* mesage );

};

//-------------------------------------------------------

struct CommandOutputMessage
{
    CommandOutputMessage(){};
};

//-------------------------------------------------------
/**
 Драйвер для соединения ICommandController
 и его подчиненных. 
*/
class ICommandOutputDriver : public QObject
{
    Q_OBJECT;

public slots:

    /**
      Слот для принятия сообщений
    */
    virtual void message( const CommandOutputMessage& ) = 0;
};

//-------------------------------------------------------

#endif //__ICOMMAND_DRIVERS

//-------------------------------------------------------

