
//-------------------------------------------------------

#ifndef  __ABSTRACT_MOVE_OBJECT__
#define  __ABSTRACT_MOVE_OBJECT__

//-------------------------------------------------------

#include <Core/PObjects/PObject.h>

//-------------------------------------------------------

class AbstractMoveObject : public PObject
{
public:
    AbstractMoveObject( const int side )
        :PObject( side, -1 ) {};

    bool canFly()const{ return false; }
    bool needManagement()const{ return true; };
};

//-------------------------------------------------------

#endif //__ABSTRACT_MOVE_OBJECT__

//-------------------------------------------------------

