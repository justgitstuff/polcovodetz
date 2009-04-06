
#include <GUI/TopLevelControls/GUIControler.h>
#include <GUI/SpecialControls/MapView.h>

#include <QGraphicsPixmapItem>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QVector>

//--------------------------------------------------------------------------

struct GUIControlerImpl
{
    MapView*                             mapView;

    QMutex                               objectsMutex;

    QVector< PtrPObject >                objects;
    QMap< qint64, uint >                 objectsIndexes;//indexes of objects
    QMap< qint64, QGraphicsPixmapItem* > drawingItems;

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

    m_impl->objects.append( obj );
    int index = m_impl->objects.count() - 1;
    m_impl->objectsIndexes.insert( obj->objectID(), index );

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem( 0, this );
    item->setPixmap( obj->image() );

    return true;
}

//--------------------------------------------------------------------------

bool GUIControler::deleteObject( const qint64 id )
{
    QMutexLocker( &m_impl->objectsMutex );

    int deletedIndex = m_impl->objectsIndexes[ id ];
    int replacedID = m_impl->objects[  m_impl->objects.count() - 1 ]->objectID();

    m_impl->objectsIndexes[ replacedID ] = deletedIndex;

    m_impl->objects[ deletedIndex ] = m_impl->objects[  m_impl->objects.count() ];

    QGraphicsPixmapItem* item = m_impl->drawingItems[ id ];
    
    removeItem( item );

    delete item;

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

