
#include <GUI/TopLevelControls/GUIControler.h>

#include <Core/PolkApp.h>
#include <GUI/SpecialControls/MapView.h>

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QVector>

//--------------------------------------------------------------------------

struct GUIControlerImpl
{
    typedef QMap< qint64, PtrPObject >           ObjectMap;
    typedef QMap< qint64, QGraphicsPixmapItem* > ViewMap;

    MapView*                             mapView;

    QMutex                               objectsMutex;

    ObjectMap                            objects;//indexes of objects
    ViewMap                              drawingItems;

    QMap< qint64, int >                  rotationMap;

    GUIControlerImpl(){ mapView = 0; }
};

//--------------------------------------------------------------------------

GUIControler::GUIControler()
            :QGraphicsScene()
{
    m_impl.reset( new GUIControlerImpl() );
};

//--------------------------------------------------------------------------

bool GUIControler::addObject( const PtrPObject& obj )
{
    QMutexLocker( &m_impl->objectsMutex );

    const qint64 id = obj->objectID();

    m_impl->objects.insert( id, obj );

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem( 0, this );
    item->setZValue( 1 );
    item->setPixmap( obj->image() );

    m_impl->drawingItems.insert( id, item );

    m_impl->rotationMap[ id ] = 0;

    return true;
}

//--------------------------------------------------------------------------

bool GUIControler::deleteObject( const qint64 id )
{
    QMutexLocker( &m_impl->objectsMutex );

    if( !m_impl->objects.contains( id ) )
        return false;

    m_impl->objects.remove( id );
    m_impl->drawingItems.remove( id );

    return true;
}

//--------------------------------------------------------------------------

void GUIControler::updateMap()
{
    if( m_impl->mapView == NULL )
        m_impl->mapView = new MapView( NULL, this );

    m_impl->mapView->updateMap();
}

//--------------------------------------------------------------------------

void GUIControler::updateObjects()
{
    for( GUIControlerImpl::ObjectMap::ConstIterator iter = m_impl->objects.constBegin();
         iter != m_impl->objects.constEnd();
         iter++ )
    {
        qint64 id = iter.key();
        PtrPObject object = iter.value();
        QGraphicsPixmapItem* view = m_impl->drawingItems[ id ];

        if( view == 0 )
            continue;

        qreal x = ((qreal)( object->position().x() * SQUARE_SIZE ) ) / PolkApp::SQUARE_SIZE;
        qreal y = ((qreal)( object->position().y() * SQUARE_SIZE ) ) / PolkApp::SQUARE_SIZE;
        
        int newRotation = object->rotation();
        const QPixmap& image = object->image();
        int width  = image.width();
        int height = image.height();

        switch( newRotation )
        {
        case 90:
            x += height;
            break;
        case 180:
            x += width;
            y += height;
            break;
        case 270:
            y += width;
            break;
        }

        view->setPos( x, y );

        int oldRotation = m_impl->rotationMap[ id ];
        if( oldRotation != newRotation )
        {
            int diff = newRotation - oldRotation;

            view->rotate( diff );

            m_impl->rotationMap[ id ] = newRotation;            
        }

    }

    
  //  update();
}

//--------------------------------------------------------------------------

