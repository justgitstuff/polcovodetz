

#ifndef  __IOBJECT_DRIVERS
#define  __IOBJECT_DRIVERS

//-------------------------------------------------------

#include <QObject>

//-------------------------------------------------------

class IObjectController;

//-------------------------------------------------------

struct ObjectInputMessage
{
    ObjectInputMessage(){};
};

//-------------------------------------------------------

class IObjectInputDriver : public QObject
{
    Q_OBJECT;

public:
    IObjectInputDriver();

signals:
    void message( ObjectInputMessage* mesage );

};

//-------------------------------------------------------

struct ObjectOutputMessage
{
    ObjectOutputMessage(){};
};

//-------------------------------------------------------

class IObjectOutputDriver : public QObject
{
    Q_OBJECT;

public:
    IObjectOutputDriver();

signals:
    void message( ObjectInputMessage* mesage );

};

//-------------------------------------------------------

#endif //__IOBJECT_DRIVERS

//-------------------------------------------------------

