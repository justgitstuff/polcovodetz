
//-------------------------------------------------------

#ifndef  __ABSTRACT_ROCKET__
#define  __ABSTRACT_ROCKET__

//-------------------------------------------------------

#include <Core/PObjects/PObject.h>

//-------------------------------------------------------

class QPixmap;

//-------------------------------------------------------

class AbstractRocket : public PObject
{
    Q_OBJECT;

public:
    AbstractRocket( const int side, const qint64 parentID )
        :PObject( side )
    {
        m_parentID = parentID;
    };

    int parentID()const{ return m_parentID; }

    virtual       bool     canFly()const{ return true; }

    virtual OnCollision    onCollision()const{ return DisposeTwice; }
    virtual       int      powerfulness()const = 0;

private:
    int m_parentID;


};

//-------------------------------------------------------

#endif //__ABSTRACT_ROCKET__

//-------------------------------------------------------

