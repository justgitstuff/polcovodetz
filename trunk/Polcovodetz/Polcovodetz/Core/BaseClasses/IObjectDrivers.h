

#ifndef  __IOBJECT_DRIVERS
#define  __IOBJECT_DRIVERS

//-------------------------------------------------------

#include <IAbstractDrivers.h>

//-------------------------------------------------------

class IObjectController;

class ObjectGroupMessage;
class GroupObjectMessage;
class ObjectCoreMessage;
class CoreObjectMessage;

//-------------------------------------------------------

class IObjectInputDriver : public IAbstractInputDriver
{
public:
    Q_OBJECT;
};

//-------------------------------------------------------

class IObjectOutputDriver : public IAbstractOutputDriver
{
    Q_OBJECT;
};

//-------------------------------------------------------

#endif //__IOBJECT_DRIVERS

//-------------------------------------------------------

