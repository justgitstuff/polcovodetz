

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
class IGroupDriver : public IAbstractInputDriver
{
    Q_OBJECT;
public:

    /**
        Посылает сообщение объекту, который имеет драйвер с заданным id.
        Если Id == -1 - сообщение рассылается ВСЕм членам данной группы
    */
    virtual void sendObjectMessage( GroupObjectMessage* ) = 0;
};

//-------------------------------------------------------

#endif //__IGROUP_DRIVERS

//-------------------------------------------------------

