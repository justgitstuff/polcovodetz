

#ifndef  __IOBJECT_DRIVERS
#define  __IOBJECT_DRIVERS

//-------------------------------------------------------

#include <QObject>

//-------------------------------------------------------

class IObjectController;

class ObjectGroupMessage;
class GroupObjectMessage;
class ObjectCoreMessage;
class CoreObjectMessage;

//-------------------------------------------------------

class IObjectInputDriver : public QObject
{
    Q_OBJECT;
};

//-------------------------------------------------------

class IObjectOutputDriver : public QObject
{
    Q_OBJECT;
};

//-------------------------------------------------------

#endif //__IOBJECT_DRIVERS

//-------------------------------------------------------

