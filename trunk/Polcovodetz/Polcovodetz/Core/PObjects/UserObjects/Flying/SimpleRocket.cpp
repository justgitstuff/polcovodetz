
//-------------------------------------------------------

#include <Core/PObjects/UserObjects/Flying/SimpleRocket.h>

#include <Core/PolkApp.h>

#include <Core/PObjects/Resources/SimpleRocket.xpm>

#include <QPixmap>
#include <QPoint>
#include <QSize>

//-------------------------------------------------------

SimpleRocket::SimpleRocket( const int side, const int parentID )
:AbstractRocket( side, parentID )
{
    
}

//-------------------------------------------------------

const QPixmap& SimpleRocket::image()const
{
    static const QPixmap image = QPixmap( simplerocket_xpm );

    return image;
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
    return QPoint( 2048, 2048 );
}

//-------------------------------------------------------

QSize SimpleRocket::boundSize()const
{    
    int width  = image().width() * PolkApp::SQUARE_SIZE / 32;
    int height = image().height() * PolkApp::SQUARE_SIZE / 32;

    if( rotation() == 90 || rotation() == 270 )
        return QSize( height, width );

    return QSize( width, height );
}

//-------------------------------------------------------

