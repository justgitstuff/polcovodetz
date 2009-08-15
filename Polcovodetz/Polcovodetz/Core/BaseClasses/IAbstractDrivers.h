
#ifndef  __IABSTRACT_DRIVERS
#define  __IABSTRACT_DRIVERS

//-------------------------------------------------------

#include <QObject>

//-------------------------------------------------------

class IAbstractDriver : public QObject
{
public:
    Q_OBJECT;
};

//-------------------------------------------------------

class IAbstractInputDriver : public IAbstractDriver
{
    Q_OBJECT;

public:
    /**
    Позволяет зарегистрировать слушатель клавиши
    */
    virtual bool registerKey( int key ) = 0;

    /**
    Вызывается ядром для уведомления нажатия клавиши
    */
    virtual void processKey( int /*key*/ ){ return; }

};

//-------------------------------------------------------

class IAbstractOutputDriver : public IAbstractDriver
{
    Q_OBJECT;
};

//-------------------------------------------------------

#endif //__IABSTRACT_DRIVERS
