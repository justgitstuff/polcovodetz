
//-------------------------------------------------------

#include <Core/PObjects/UserObjects/Moving/SimpleTank.h>

#include <Core/PolkApp.h>
#include <Core/PObjects/UserObjects/Flying/SimpleRocket.h>

#include <Core/PObjects/Resources/BlueSimpleTank.xpm>
#include <Core/PObjects/Resources/RedSimpleTank.xpm>

#include <QObject>
#include <QPixmap>
#include <QPoint>
#include <QSize>

//-------------------------------------------------------

SimpleTank::SimpleTank( const int side )
:AbstractMoveObject( side )
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
    info.name = QObject::tr( "SimpleTank" );
    info.description = QObject::tr( "SimpleTank" );

    return info;
}

//-------------------------------------------------------

QPoint SimpleTank::maxSpeed()const
{     
    return QPoint( 1024, 1024 );
}

//-------------------------------------------------------

QSize SimpleTank::boundSize()const
{
    int width  = image().width() * PolkApp::SQUARE_SIZE / 32;
    int height = image().height() * PolkApp::SQUARE_SIZE / 32;

    if( rotation() == 90 || rotation() == 270 )
        return QSize( height, width );

    return QSize( width, height );
}

//-------------------------------------------------------

int SimpleTank::atackObject()const
{
    return SimpleRocket::RTTI;
}

//-------------------------------------------------------

int SimpleTank::shootCount()const
{
    return 1000000;
}

//-------------------------------------------------------

int SimpleTank::maxShootOnPane()const
{
    return 2;
}

//-------------------------------------------------------

QPoint SimpleTank::startPoint()const
{
    QSize size = boundSize();

    int x = position().x();
    int y = position().y();

    switch( rotation() )
    {
    case 0:
        x += size.width() / 2;
        break;

    case 90:
        x += size.width();
        y += size.height() / 2;
        break;

    case 180:
        x += size.width() / 2;
        y += size.height();
        break;

    case 270:
        y += size.height() / 2;
        break;
   }
    
    return QPoint( x, y );
}

//-------------------------------------------------------

