

#ifndef  __IGROUP_DRIVERS
#define  __IGROUP_DRIVERS

//-------------------------------------------------------

#include <IAbstractDrivers.h>

//-------------------------------------------------------

class IGroupController;

class ObjectGroupMessage;
class GroupObjectMessage;
class GroupCommandMessage;
class CommandGroupMessage;

//-------------------------------------------------------
/**
 Драйвер для соединения IGroupController и PolkApp
*/
class IGroupInputDriver : public IAbstractInputDriver
{
    Q_OBJECT;

signals:
    /**
        Сигнал приема сообщений.
    */
    void message( CommandGroupMessage* mesage );
    void message( ObjectGroupMessage* mesage );
};

//-------------------------------------------------------

struct GroupOutputMessage
{
    GroupOutputMessage(){};
};

//-------------------------------------------------------
/**
 Драйвер для соединения ICommandController
 и его подчиненных. 
*/
class IGroupOutputDriver : public IAbstractOutputDriver
{
    Q_OBJECT;
};

//-------------------------------------------------------

#endif //__IGROUP_DRIVERS

//-------------------------------------------------------

