

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
};

//-------------------------------------------------------

#endif //__IGROUP_DRIVERS

//-------------------------------------------------------

