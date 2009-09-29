

#ifndef  __SIMPLE_OBJECT_DRIVERS
#define  __SIMPLE_OBJECT_DRIVERS

//-------------------------------------------------------

#include <Core/PObjects/PObject.h>
#include <IObjectDrivers.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct SimpleObjectDriverImpl;

class IGroupOutputDriver;

class CommandState;

//-------------------------------------------------------

/**

*/
class SimpleObjectDriver : public IObjectDriver
{
    Q_OBJECT;

public:
    SimpleObjectDriver( CommandState* state );
    ~SimpleObjectDriver();

    bool init( const boost::shared_ptr< IObjectController >& );
   
    virtual PtrPObject& pObject();

    bool oConnect( const PtrPObject& object );

    MovementDirection nearesPointToFlag()const;
    
    bool registerKey( Qt::Key key );

    /**
    Вызывается ядром для уведомления нажатия клавиши
    */
    virtual void processKey( Qt::Key key );

    /**
        Устанавливает скорость как процент от максимальной.
        Значения - от 0 до 100
    */
    virtual void setSpeed( const int persent );

    /**
        Устанавливает текущий поворот объекта
    */
    virtual void setRotation( const ObjectRotation& rotation );    
   
    /**
        Выпускает снаряд
    */
    virtual void makeAttack();

private:
    boost::shared_ptr< SimpleObjectDriverImpl > m_impl;
};

//-------------------------------------------------------

#endif //__SIMPLE_OBJECT_DRIVERS

//-------------------------------------------------------

