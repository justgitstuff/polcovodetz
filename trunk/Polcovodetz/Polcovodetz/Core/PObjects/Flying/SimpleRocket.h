
//-------------------------------------------------------

#ifndef  __SIMPLE_ROCKET__
#define  __SIMPLE_ROCKET__

//-------------------------------------------------------

#include <Core/PObjects/UserObjects/AbstractRocket.h>

//-------------------------------------------------------

class QPixmap;

//-------------------------------------------------------

class SimpleRocket : public AbstractRocket
{
    Q_OBJECT;

public:
    SimpleRocket( const int side );

    virtual const QPixmap& image()const;
    virtual       int      rtti()const{ return SimpleRocket::RTTI; }
    
    virtual       QSize    boundSize()const;

    virtual       bool     canFly()const{ return true; }

    virtual       QPoint   maxSpeed()const;
    virtual OnCollision    onCollision()const{ return DisposeTwice; }
    virtual OnCollision    onStop()const{ return DisposeTwice; }



    static PObjectInfo info();

    static const int RTTI = 2;
};

//-------------------------------------------------------

#endif //__SIMPLE_ROCKET__

//-------------------------------------------------------

