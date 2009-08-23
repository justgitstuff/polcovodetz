
//--------------------------------------------------------------------------

#include <GUI/SpecialControls/PaintArea2D.h>

#include <Core/Common/Map.h>
#include <Core/PObjects/PObject.h>
#include <Core/PolkApp.h>

#include <QResizeEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMap>
#include <QMessageBox>
#include <QMutex>
#include <QMutexLocker>

//--------------------------------------------------------------------------

struct PaintArea2DImpl
{
    QMutex                               objectsMutex;

    QVector< PtrPObject >                objects;
    QMap< qint64, uint >                 objectsIndexes;//indexes of objects
    QMap< qint64, QGraphicsPixmapItem* > drawingItems;
};

//--------------------------------------------------------------------------

PaintArea2D::PaintArea2D( QGraphicsScene* scene, QWidget* parent )
:QGraphicsView( scene, parent )
{
    m_scene                 = scene;

    m_impl.reset( new PaintArea2DImpl() );
}

//--------------------------------------------------------------------------

PaintArea2D::~PaintArea2D()
{
}

//--------------------------------------------------------------------------

void PaintArea2D::resizeEvent( QResizeEvent* event )
{
    const int pWidth  = pApp.map().width() * 32;
    const int pHeight = pApp.map().height() * 32;

    const qreal min = qMin( size().rwidth(), size().rheight() );

    const qreal w = ( (qreal)pWidth )  * size().rwidth()  / min;
    const qreal h = ( (qreal)pHeight ) * size().rheight() / min;

    QGraphicsView::resizeEvent( event );

    fitInView( 0, 0, w, h );
}

//--------------------------------------------------------------------------
 
void PaintArea2D::keyPressEvent( QKeyEvent* key )
{
    pApp.userPressKey( ( Qt::Key )key->key() );
}

//--------------------------------------------------------------------------
