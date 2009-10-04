
//-------------------------------------------------------

#include <Core/Common/MovementDirection.h>

#include <QPoint>

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
/*
MovementDirection::~MovementDirection()
{

}
*/
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

MovementDirection MovementDirection::createDirection( const QPoint& from, const QPoint& to )
{
    if( from.x() == to.x() )
    {
        if( from.y() > to.y() )
            return MovementDirection( Top );

        if( from.y() < to.y() )
            return MovementDirection( Down );
    }
    if( from.y() == to.y() )
    {
        if( from.x() > to.x() )
            return MovementDirection( Left );

        if( from.x() < to.x() )
            return MovementDirection( Right );
    }

    return MovementDirection();
}

//-------------------------------------------------------


