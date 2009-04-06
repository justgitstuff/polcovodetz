

#ifndef  __IGROUP_DRIVERS
#define  __IGROUP_DRIVERS

//-------------------------------------------------------

#include <QObject>

//-------------------------------------------------------

class IGroupController;

//-------------------------------------------------------
/**
  Сообщение, посылаемое к IGroupController
*/
struct GroupInputMessage
{
    GroupInputMessage(){};
};

//-------------------------------------------------------
/**
 Драйвер для соединения IGroupController и PolkApp
*/
class IGroupInputDriver : public QObject
{
    Q_OBJECT;

public:
    IGroupInputDriver();

signals:
    void message( GroupInputMessage* mesage );
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

public:
    IGroupOutputDriver();

signals:
    void message( GroupInputMessage* mesage );

};

//-------------------------------------------------------

#endif //__IGROUP_DRIVERS

//-------------------------------------------------------

