

#ifndef  __IOBJECT_DRIVERS
#define  __IOBJECT_DRIVERS

//-------------------------------------------------------

#include <IAbstractDrivers.h>
#include <PObject.h>
#include <MovementDirection.h>

//-------------------------------------------------------

class IObjectController;

class ObjectGroupMessage;
class GroupObjectMessage;
class ObjectCoreMessage;
class CoreObjectMessage;

//-------------------------------------------------------

enum ObjectRotation
{ 
    ToTop, 
    ToBottom, 
    ToLeft, 
    ToRight 
};

//-------------------------------------------------------
/**
    Драйвер, отвечающий за взаимодействия с коммандиров группы
*/
class IObjectInputDriver : public IAbstractInputDriver
{
public:
    Q_OBJECT;

    virtual MovementDirection nearesPointToFlag()const = 0;

signals:
    /**
        Сигнал приема сообщений.
    */
    void message( GroupObjectMessage* mesage );
};

//-------------------------------------------------------
/**
    Драйвер, отвечающий за взаимодействие коммандира объекта с 
    самим объектов, если он создан
*/
class IObjectOutputDriver : public IAbstractOutputDriver
{
    Q_OBJECT;

public:

    virtual PtrPObject& pObject() = 0;

    /**
        Устанавливает скорость как процент от максимальной.
        Значения - от 0 до 100
    */
    virtual void setSpeed( const int persent ) = 0;

    /**
        Устанавливает текущий поворот объекта
    */
    virtual void setRotation( const ObjectRotation& rotation ) = 0;
   
    /**
        Выпускает снаряд
    */
    virtual void makeAttack() = 0;
};

//-------------------------------------------------------

#endif //__IOBJECT_DRIVERS

//-------------------------------------------------------

