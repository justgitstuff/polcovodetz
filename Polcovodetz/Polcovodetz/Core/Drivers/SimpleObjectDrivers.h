

#ifndef  __SIMPLE_OBJECT_DRIVERS
#define  __SIMPLE_OBJECT_DRIVERS

//-------------------------------------------------------

#include <Core/PObjects/PObject.h>
#include <IObjectDrivers.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct SimpleObjectInputDriverImpl;
struct SimpleObjectOutputDriverImpl;

class IGroupOutputDriver;

class CommandState;

//-------------------------------------------------------

/**

*/
class SimpleObjectInputDriver : public IObjectInputDriver
{
    Q_OBJECT;

public:
    SimpleObjectInputDriver();
    ~SimpleObjectInputDriver();

    bool init( const boost::shared_ptr< IObjectController >& );

    bool dConnect( const boost::shared_ptr< IGroupOutputDriver >& );
    
    bool registerKey( Qt::Key key );

    /**
    Вызывается ядром для уведомления нажатия клавиши
    */
    virtual void processKey( Qt::Key key );

private:
    boost::shared_ptr< SimpleObjectInputDriverImpl > m_impl;
};

//-------------------------------------------------------
/**
 
*/
class SimpleObjectOutputDriver : public IObjectOutputDriver
{
    Q_OBJECT;

public:
    SimpleObjectOutputDriver( CommandState* state );

    bool init( const boost::shared_ptr< IObjectController >& );

    bool dConnect( const PtrPObject& );
    
    virtual PtrPObject& pObject();

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
    boost::shared_ptr< SimpleObjectOutputDriverImpl > m_impl;
};

//-------------------------------------------------------

#endif //__SIMPLE_OBJECT_DRIVERS

//-------------------------------------------------------

