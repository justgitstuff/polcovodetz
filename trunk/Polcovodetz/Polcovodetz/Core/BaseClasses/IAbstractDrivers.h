
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
    virtual bool registerKey( int key ) = 0;

    /**
    ���������� ����� ��� ����������� ������� �������
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
