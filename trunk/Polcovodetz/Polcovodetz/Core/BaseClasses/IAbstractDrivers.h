
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
    ��������� ���������������� ��������� �������
    */
    virtual bool registerKey( Qt::Key key ) = 0;

    /**
    ���������� ����� ��� ����������� ������� �������
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
