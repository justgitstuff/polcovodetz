#ifndef MAPOPERATIONS_H
#define MAPOPERATIONS_H

//-------------------------------------------------------

#include <boost/shared_ptr.hpp>
#include <Core/Common/MovementDirection.h>

#include <QPoint.h>

//-------------------------------------------------------

class Map;
struct MapOperationsImpl;

//-------------------------------------------------------

class MapOperations
{
public:
    MapOperations( const Map& );
    ~MapOperations();

    MovementDirection nearestPointFromPath( const QPoint& start, const QPoint& stop )const;

    QPoint            flagPoint( int side )const;

private:
    boost::shared_ptr< MapOperationsImpl > m_impl;
    
};

//-------------------------------------------------------

#endif // MAPOPERATIONS_H

//-------------------------------------------------------

