
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

    int index;
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

void GUIControler::deleteObject( const qint64 id )
{
    QMutexLocker( &m_impl->objectsMutex );

    if( !m_impl->objects.contains( id ) )
        return;

    m_impl->objects.remove( id );

    QGraphicsPixmapItem* item = m_impl->drawingItems[ id ];

    QGraphicsScene::removeItem( item );

    m_impl->drawingItems.remove( id );

    delete item;
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

        int x = ( object->position().x() * SQUARE_SIZE ) / PolkApp::SQUARE_SIZE;
        int y = ( object->position().y() * SQUARE_SIZE ) / PolkApp::SQUARE_SIZE;
        
        int newRotation = object->rotation();
        const QPixmap& image = object->image();

        int width  = image.width();
        int height = image.height();

        int oldRotation = m_impl->rotationMap[ id ];
        if( oldRotation != newRotation )
        {
            view->setPixmap( object->image( newRotation ) );

            m_impl->rotationMap[ id ] = newRotation;  

            update( QRect( x - width/2, y-height/2, width*2, height*2 ) );
        }

        view->setPos( x, y );
    }

    if( m_impl->index % 400 == 0 )
        update();
  //  update();
}

//--------------------------------------------------------------------------

