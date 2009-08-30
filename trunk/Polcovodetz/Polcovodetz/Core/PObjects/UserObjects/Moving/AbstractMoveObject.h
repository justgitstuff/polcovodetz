
//-------------------------------------------------------

#ifndef  __ABSTRACT_MOVE_OBJECT__
#define  __ABSTRACT_MOVE_OBJECT__

//-------------------------------------------------------

#include <Core/PObjects/PObject.h>

//-------------------------------------------------------

class AbstractMoveObject : public PObject
{
    Q_OBJECT;

public:
    AbstractMoveObject( const int side )
        :PObject( side )
    {};

    bool canFly()const{ return false; }

private:
};

//-------------------------------------------------------

#endif //__ABSTRACT_MOVE_OBJECT__

//-------------------------------------------------------

