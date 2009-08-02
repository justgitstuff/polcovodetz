

#ifndef  __IGROUP_DRIVERS
#define  __IGROUP_DRIVERS

//-------------------------------------------------------

#include <QObject>

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
class IGroupInputDriver : public QObject
{
    Q_OBJECT;
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
class IGroupOutputDriver : public QObject
{
    Q_OBJECT;
};

//-------------------------------------------------------

#endif //__IGROUP_DRIVERS

//-------------------------------------------------------

