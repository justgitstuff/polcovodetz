
//-------------------------------------------------------

#ifndef  __I_SHOOTABLE_OBJECT__
#define  __I_SHOOTABLE_OBJECT__

//-------------------------------------------------------

class IShootableObject
{
public:
    /**
        ������ RTTI �������, ������ �������.
    */
    virtual int  atackObject()const    = 0;

    /**
        ����� ���������� ��������� ���������
    */
    virtual int  shootCount()const     = 0;

    /**
        ������������ ���������� ����� �� ����
    */
    virtual int  maxShootOnPane()const = 0;

    /**
        ����� ��� ������ ������
    */
    virtual QPoint startPoint()const = 0;
};

//-------------------------------------------------------

#endif //__I_SHOOTABLE_OBJECT__

//-------------------------------------------------------

