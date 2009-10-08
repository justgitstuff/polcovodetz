
//-------------------------------------------------------

#include <MathUtils.h>

//-------------------------------------------------------

QPoint rotatePoint( const QPoint& base, const int angle )
{   
    QPoint result( base );

    switch( angle )
    {
    case 0:
        {
            result.setX( base.y() );
            result.setY( -base.x() );
            break;
        }

    case 90:
        break;

    case 180:
        {
            result.setX( -base.y() );
            result.setY(  base.x() );
            break;
        }

    case 270:
        result.setX( -base.x() );
        result.setY( -base.y() );
        break;

    default:
        result.setX( 0 );
        result.setY( 0 );
    }

    return result;
}

//-------------------------------------------------------

