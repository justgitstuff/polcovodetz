
//-------------------------------------------------------

#include <Core/PObjects/UserObjects/Moving/SimpleTank.h>

#include <Core/PolkApp.h>

#include <Core/PObjects/Resources/BlueSimpleTank.xpm>
#include <Core/PObjects/Resources/RedSimpleTank.xpm>

#include <QPixmap>
#include <QPoint>
#include <QSize>

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
    return QPoint( 10, 10 );
}

//-------------------------------------------------------

QSize SimpleTank::boundSize()const
{
    return QSize( PolkApp::SQUARE_SIZE * 8 / 10, PolkApp::SQUARE_SIZE * 8 / 10 );
}

//-------------------------------------------------------

