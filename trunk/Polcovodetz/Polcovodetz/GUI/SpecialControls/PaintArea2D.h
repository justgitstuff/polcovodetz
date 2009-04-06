

#ifndef  __PAINT_AREA_2D
#define  __PAINT_AREA_2D

//-----------------------------------------------------------------

#include <QGraphicsView>

#include <GUI/TopLevelControls/GUIControler.h>

#include <boost/shared_ptr.hpp>

//-----------------------------------------------------------------

struct PaintArea2DImpl;

class QResizeEvent;

//-----------------------------------------------------------------

class PaintArea2D : public QGraphicsView
{
    Q_OBJECT;
public:
    PaintArea2D( QGraphicsScene* m_scene, QWidget* parent );
    ~PaintArea2D();

 //   bool  addObject( const PtrPObject& ); //with lock
 //   bool  deleteObject( const qint64 id );//with lock

protected:
    void resizeEvent( QResizeEvent* );

private:
    boost::shared_ptr< PaintArea2DImpl > m_impl;

    QGraphicsScene* m_scene;

    double          m_scaleX;
    double          m_scaleY;
};

//-----------------------------------------------------------------

#endif //__PAINT_AREA_2D

//-----------------------------------------------------------------
