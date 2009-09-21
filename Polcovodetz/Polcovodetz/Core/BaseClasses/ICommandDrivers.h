

#ifndef  __ICOMMAND_DRIVERS
#define  __ICOMMAND_DRIVERS

//-------------------------------------------------------

#include <IAbstractDrivers.h>

//-------------------------------------------------------

class ICommandController;

class CoreCommandMessage;
class GroupCommandMessage;
class CommandCoreMessage;
class CommandGroupMessage;

//-------------------------------------------------------
/**
 Драйвер для соединения ICommandController
 и CommandThreasd . В целом, передача сообщения должна выполняться так
 1) Уведомить CommandThread о новом сообщении ( т. е. передать ему его )
 2) Когда подойдет его очереь, будет запущена функция ICommandInputDriver::message( CoreCommandMessage* mesage )
*/
class ICommandInputDriver : public IAbstractInputDriver
{
    Q_OBJECT;

public:
    virtual void sendMessage( CoreCommandMessage* ) = 0;
    virtual void sendMessage( GroupCommandMessage* ) = 0;

signals:
    /**
        Сигнал приема сообщений.
    */
    void message( CoreCommandMessage* mesage );
    void message( GroupCommandMessage* mesage );

};

//-------------------------------------------------------
/**
 Драйвер для соединения ICommandController
 и его подчиненных. 
*/
class ICommandOutputDriver : public IAbstractOutputDriver
{
    Q_OBJECT;

public:
    virtual void createObjectForDriver( const qint64 driverID, const int objectRTTI ) = 0;
};

//-------------------------------------------------------

#endif //__ICOMMAND_DRIVERS

//-------------------------------------------------------

