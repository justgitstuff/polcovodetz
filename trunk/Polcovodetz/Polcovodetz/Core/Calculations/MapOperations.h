#ifndef MAPOPERATIONS_H
#define MAPOPERATIONS_H

//-------------------------------------------------------

#include <boost/shared_ptr.hpp>
#include <Core/MovementDirection.h>

//-------------------------------------------------------

class Map;
struct MapOperationsImpl;

class QPoint;

//-------------------------------------------------------

class MapOperations
{
public:
    MapOperations( const Map& );
    ~MapOperations();

    MovementDirection nearestPointFromPath( const QPoint& start, const QPoint& stop );

private:
    boost::shared_ptr< MapOperationsImpl > m_impl;
    
};

//-------------------------------------------------------

#endif // MAPOPERATIONS_H

//-------------------------------------------------------

