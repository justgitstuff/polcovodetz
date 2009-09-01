
//-------------------------------------------------------

#include <Core/PObjects/Flying/SimpleRocket.h>

#include <Core/PolkApp.h>

#include <Core/PObjects/Resources/BlueSimpleTank.xpm>
#include <Core/PObjects/Resources/RedSimpleTank.xpm>

#include <QPixmap>
#include <QPoint>
#include <QSize>

//-------------------------------------------------------

SimpleRocket::SimpleRocket( const int side )
:PObject( side )
{
    
}

//-------------------------------------------------------

const QPixmap& SimpleRocket::image()const
{
    static const QPixmap blueTank = QPixmap( bluesimpletank_xpm );
    static const QPixmap redTank  = QPixmap( redsimpletank_xpm );

    if( side() == 1 )
        return blueTank;

    return redTank;
}

//-------------------------------------------------------

PObjectInfo SimpleRocket::info()
{
    PObjectInfo info;

    info.id = SimpleRocket::RTTI;
    info.name = tr( "SimpleRocket" );
    info.description = tr( "SimpleRocket" );

    return info;
}

//-------------------------------------------------------

QPoint SimpleRocket::maxSpeed()const
{     
    return QPoint( 1024, 1024 );
}

//-------------------------------------------------------

QSize SimpleRocket::boundSize()const
{
    return QSize( 10, 10 );/*
    int width  = image().width() * PolkApp::SQUARE_SIZE / 32;
    int height = image().height() * PolkApp::SQUARE_SIZE / 32;

    if( rotation() == 90 || rotation() == 270 )
        return QSize( height, width );

    return QSize( width, height );*/
}

//-------------------------------------------------------

