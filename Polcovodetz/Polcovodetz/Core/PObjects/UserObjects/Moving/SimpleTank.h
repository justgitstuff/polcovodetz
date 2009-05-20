
//-------------------------------------------------------

#ifndef  __SIMPLE_TANK__
#define  __SIMPLE_TANK__

//-------------------------------------------------------

#include <Core/PObjects/PObject.h>

//-------------------------------------------------------

class QPixmap;

//-------------------------------------------------------

class SimpleTank : public PObject
{
    Q_OBJECT;

public:
    SimpleTank( const int side ):PObject( side ){};

    virtual const QPixmap& image()const;
    virtual       int      rtti()const{ return SimpleTank::RTTI; }

    static PObjectInfo info();

    static const int RTTI = 1;
};

//-------------------------------------------------------

#endif //__SIMPLE_TANK__

//-------------------------------------------------------

