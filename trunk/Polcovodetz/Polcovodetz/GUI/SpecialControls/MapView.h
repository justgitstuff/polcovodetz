
//-------------------------------------------------------------

#ifndef  __MAP_VIEW
#define  __MAP_VIEW

//-------------------------------------------------------------

#include <QGraphicsPixmapItem>

//-------------------------------------------------------------

class BattleState;
class QTextStream;

//-------------------------------------------------------------

class MapView : public QGraphicsPixmapItem
{
public:
    MapView( QGraphicsItem* = NULL, QGraphicsScene* = NULL );

    void updateMap();

private:
    QPixmap createBackground();
};

//-------------------------------------------------------------

#endif //__MAP_VIEW