
//-------------------------------------------------------

#ifndef  __I_SHOOTABLE_OBJECT__
#define  __I_SHOOTABLE_OBJECT__

//-------------------------------------------------------

class IShootableObject
{
public:
    /**
        Выдает RTTI объекта, которм атакует.
    */
    virtual int  atackObject()const    = 0;

    /**
        Общее количество возможных выстрелов
    */
    virtual int  shootCount()const     = 0;

    /**
        Максимальное количество ракет на поле
    */
    virtual int  maxShootOnPane()const = 0;

    /**
        Точка для старта ракеты
    */
    virtual QPoint startPoint()const = 0;
};

//-------------------------------------------------------

#endif //__I_SHOOTABLE_OBJECT__

//-------------------------------------------------------

