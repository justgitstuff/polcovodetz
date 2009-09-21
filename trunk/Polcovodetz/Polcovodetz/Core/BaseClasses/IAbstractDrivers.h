
#ifndef  __IABSTRACT_DRIVERS
#define  __IABSTRACT_DRIVERS

//-------------------------------------------------------

#include <QObject>

//-------------------------------------------------------

class IAbstractDriver : public QObject
{
    Q_OBJECT;
public:
    IAbstractDriver()
    {
        static volatile qint64 id = 1;

        m_id = id++;
    }

    qint64 driverID()const{ return m_id; }

private:
    qint64 m_id;
};

//-------------------------------------------------------

class IAbstractInputDriver : public IAbstractDriver
{
    Q_OBJECT;

public:
    /**
    Позволяет зарегистрировать слушатель клавиши
    */
    virtual bool registerKey( Qt::Key key ) = 0;

    /**
    Вызывается ядром для уведомления нажатия клавиши
    */
    virtual void processKey( Qt::Key /*key*/ ){ return; }

};

//-------------------------------------------------------

class IAbstractOutputDriver : public IAbstractDriver
{
    Q_OBJECT;
};

//-------------------------------------------------------

#endif //__IABSTRACT_DRIVERS
