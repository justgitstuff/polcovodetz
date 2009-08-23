
//-------------------------------------------------------

#include <Core/PObjects/UserObjects/Moving/SimpleTank.h>

#include <Core/PObjects/Resources/BlueSimpleTank.xpm>
#include <Core/PObjects/Resources/RedSimpleTank.xpm>

#include <QPixmap>
#include <QPoint>

//-------------------------------------------------------

SimpleTank::SimpleTank( const int side )
:PObject( side )
{
    
}

//-------------------------------------------------------

const QPixmap& SimpleTank::image()const
{
    static const QPixmap blueTank = QPixmap( bluesimpletank_xpm );
    static const QPixmap redTank  = QPixmap( redsimpletank_xpm );

    if( side() == 1 )
        return blueTank;

    return redTank;
}

//-------------------------------------------------------

PObjectInfo SimpleTank::info()
{
    PObjectInfo info;

    info.id = SimpleTank::RTTI;
    info.name = tr( "SimpleTank" );
    info.description = tr( "SimpleTank" );

    return info;
}

//-------------------------------------------------------

QPoint SimpleTank::maxSpeed()const
{     
    return QPoint( 1, 1 );
}

//-------------------------------------------------------

