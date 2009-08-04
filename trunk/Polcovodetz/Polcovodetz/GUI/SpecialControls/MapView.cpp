
#include <GUI/SpecialControls/MapView.h>

#include <Core/Common/Map.h>
#include <Core/PolkApp.h>

#include <GUI/SpecialControls/Resources/Map/Empty.xpm>
#include <GUI/SpecialControls/Resources/Map/Brick.xpm>
#include <GUI/SpecialControls/Resources/Map/Grassland.xpm>
#include <GUI/SpecialControls/Resources/Map/Stone.xpm>
#include <GUI/SpecialControls/Resources/Map/Water.xpm>
#include <GUI/SpecialControls/Resources/Map/BlueStartPlace.xpm>
#include <GUI/SpecialControls/Resources/Map/RedStartPlace.xpm>

#include <QPainter>

//-------------------------------------------------------------------

QPixmap mergePixmap( const QPixmap& background, const QPixmap& data )
{
    QPixmap  pixmap( background );

    QPainter painter( &pixmap );

    painter.drawPixmap( 0, 0, data );

    return pixmap;
}

//-------------------------------------------------------------------

const QPixmap& createMapObject( const MapObject object )
{    
    static const QPixmap empty( empty_xpm );
    static const QPixmap brick( brick_xpm );
    static const QPixmap grass( grassland_xpm );
    static const QPixmap stone( stone_xpm );
    static const QPixmap water( water_xpm );

    static const QPixmap blueStartPlace = mergePixmap( empty, QPixmap(  bluestartplace_xpm ) );
    static const QPixmap redStartPlace  = mergePixmap( empty, QPixmap( redstartplace_xpm ) );    

    switch( object )
    {
    case Brick :
        return brick;
    case Water :
        return water;
    case Stone :
        return stone;
    case Grassland :
        return grass;
    case FirstCommandBox :
        return blueStartPlace;
    case SecondCommandBox :
        return redStartPlace;
    default:
        return empty;
    }
}

//-------------------------------------------------------------------

MapView::MapView( QGraphicsItem* parent, QGraphicsScene* scene )
:QGraphicsPixmapItem( parent, scene )
{
}

//-------------------------------------------------------------------

QPixmap MapView::createBackground()
{    
    const int rectangleWigth  = 32;
    const int rectangleHeight = 32;
    
    QPixmap pixmap( rectangleWigth  * pApp.map().width(), 
                    rectangleHeight * pApp.map().height() );

    QPainter painter( &pixmap );

    for( int x = 0; x < pApp.map().width(); x ++ )
    {
        for( int y = 0; y < pApp.map().height(); y ++ )
        {
            MapObject who = pApp.map().objectAt( x, y );

            painter.drawPixmap( x * rectangleWigth, y * rectangleHeight, createMapObject( who ) );
        }
    }

    return pixmap;
}

//-------------------------------------------------------------------

void MapView::updateMap()
{
    setPixmap( createBackground() );
}

//-------------------------------------------------------------------

