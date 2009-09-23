
//-------------------------------------------------------

#include <Core/MovementDirection.h>

//-------------------------------------------------------

struct MovementDirectionImpl
{
    int  direction;
    bool isNull;
};

//-------------------------------------------------------

MovementDirection::MovementDirection( int angle )
:m_impl( new MovementDirectionImpl() )
{
    setDirection( angle );
}

//-------------------------------------------------------

MovementDirection::~MovementDirection()
{

}

//-------------------------------------------------------

bool MovementDirection::isNull()const
{
    return m_impl->isNull;
}

//-------------------------------------------------------

int MovementDirection::direction()const
{
    return m_impl->direction;
}

//-------------------------------------------------------

void MovementDirection::setDirection( int direction )
{
    m_impl->direction = direction;
    
    m_impl->isNull = ( direction < 0 ) || ( direction > 360 );
}

//-------------------------------------------------------


