
//-------------------------------------------------------

#ifndef  __SIMPLE_TANK__
#define  __SIMPLE_TANK__

//-------------------------------------------------------

#include <Core/PObjects/UserObjects/Moving/AbstractMoveObject.h>
#include <Core/PObjects/Interfaces/IShootableObject.h>

//-------------------------------------------------------

class QPixmap;

//-------------------------------------------------------

class SimpleTank : public AbstractMoveObject, public IShootableObject
{
    Q_OBJECT;

public:
    SimpleTank( const int side );

    virtual const QPixmap& image()const;
    virtual       int      rtti()const{ return SimpleTank::RTTI; }
    
    virtual       QSize    boundSize()const;

    virtual       QPoint   maxSpeed()const;
    virtual OnCollision    onCollision()const{ return Revert; }
    virtual OnCollision    onStop()const{ return Revert; }

    /**
        Выдает RTTI объекта, которм атакует.
    */
    virtual int  atackObject()const;

    /**
        Общее количество возможных выстрелов
    */
    virtual int  shootCount()const;

    /**
        Максимальное количество ракет на поле
    */
    virtual int  maxShootOnPane()const;


    static PObjectInfo info();

    static const int RTTI = 1;
};

//-------------------------------------------------------

#endif //__SIMPLE_TANK__

//-------------------------------------------------------

