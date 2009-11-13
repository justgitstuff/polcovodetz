
#include <GUI/TopLevelControls/GUIControler.h>

#include <Core/PolkApp.h>
#include <GUI/SpecialControls/CrashImageItem.h>
#include <GUI/SpecialControls/MapView.h>

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QQueue>
#include <QVector>

//--------------------------------------------------------------------------

struct GUIControlerImpl
{
    typedef QMap< qint64, PtrPObject >            ObjectMap;
    typedef QMap< qint64, QGraphicsPixmapItem* >  ViewMap;
    typedef boost::shared_ptr< CrashImageItem >   PtrCrashItem;
    typedef QQueue< PtrCrashItem >                CrashItems;

    GUIControler*                        parent;
    MapView*                             mapView;

    QMutex                               objectsMutex;

    ObjectMap                            objects;//indexes of objects
    ViewMap                              drawingItems;

    QMap< qint64, int >                  rotationMap;

    GUIControlerImpl( GUIControler* parent ){ mapView = 0; this->parent = parent; }

    int index;

    CrashItems crashItems;

    void cleanCrashItems();
    void updateCrashItems();
};

//--------------------------------------------------------------------------

void GUIControlerImpl::updateCrashItems()
{
    for( CrashItems::Iterator iter = crashItems.begin();
         iter != crashItems.end();
         iter ++ )
    {
        iter->get()->nextStep();
    }
}

//--------------------------------------------------------------------------

void GUIControlerImpl::cleanCrashItems()
{
    if( crashItems.isEmpty() )
        return;

    boost::shared_ptr< CrashImageItem > last = crashItems.last();

    while( last->needDelete() )
    {
        parent->removeItem( last.get() );

        crashItems.pop_back();

        if( crashItems.isEmpty() )
            return;

        last = crashItems.last();
    }
}

//--------------------------------------------------------------------------

GUIControler::GUIControler()
            :QGraphicsScene()
{
    m_impl.reset( new GUIControlerImpl( this ) );
};

//--------------------------------------------------------------------------

void GUIControler::addPObject( const PtrPObject& obj )
{
    const qint64 id = obj->objectID();

    m_impl->objects.insert( id, obj );

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem( obj->image(), 0, this );
    item->setZValue( 1 );
    updatePosition( obj, item );

    m_impl->drawingItems.insert( id, item );

    m_impl->rotationMap[ id ] = 0;
}

//--------------------------------------------------------------------------

void GUIControler::deleteObject( const qint64 id )
{
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

void GUIControler::updatePosition( const PtrPObject& object, QGraphicsPixmapItem* view )
{
    qint64 id = object->objectID();

    int x = ( object->position().x() * SQUARE_SIZE ) / PolkApp::SQUARE_SIZE;
    int y = ( object->position().y() * SQUARE_SIZE ) / PolkApp::SQUARE_SIZE;

    view->setPos( x, y );
    
    int newRotation = object->rotation();

    int oldRotation = m_impl->rotationMap[ id ];

    if( oldRotation != newRotation )
    {
        view->setPixmap( object->image( newRotation ) );

        m_impl->rotationMap[ id ] = newRotation;  
    }
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

        updatePosition( object, view );
    }

    m_impl->updateCrashItems();
    m_impl->cleanCrashItems();

   /* if( m_impl->index % 400 == 0 )
        update();*/
}

//--------------------------------------------------------------------------

void GUIControler::addCrashMark( const QPoint& where )
{
    GUIControlerImpl::PtrCrashItem newItem( new CrashImageItem( this ) );

    QPoint newPosition( where.x() - PolkApp::SQUARE_SIZE / 2, where.y() - PolkApp::SQUARE_SIZE / 2 );

    newPosition = ( newPosition * SQUARE_SIZE ) / PolkApp::SQUARE_SIZE;

    newItem->setPos( newPosition );

    addItem( newItem.get() );

    m_impl->crashItems.push_front( newItem );
}

//--------------------------------------------------------------------------

