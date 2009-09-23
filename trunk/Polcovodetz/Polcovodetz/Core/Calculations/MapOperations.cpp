
//-------------------------------------------------------

#include <Core/Calculations/MapOperations.h>
#include <Core/Common/Map.h>

//-------------------------------------------------------

struct MapOperationsImpl
{
    Map map;
};

//-------------------------------------------------------

MapOperations::MapOperations( const Map& map )
:m_impl( new MapOperationsImpl() )
{
    m_impl->map = map;
}

//-------------------------------------------------------

MapOperations::~MapOperations()
{

}

//-------------------------------------------------------

MovementDirection MapOperations::nearestPointFromPath( const QPoint& start, const QPoint& stop )
{
    return MovementDirection();
}

//-------------------------------------------------------

