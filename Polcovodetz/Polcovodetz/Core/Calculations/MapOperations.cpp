
//-------------------------------------------------------

#include <Core/Calculations/MapOperations.h>
#include <Core/Common/DualArray.h>
#include <Core/Common/Map.h>
#include <Core/PolkApp.h>

#include <QMap>
#include <QPair>
#include <QQueue>

//-------------------------------------------------------

class MyPoint : public QPoint
{
public:
    MyPoint( const QPoint& p = QPoint() )
        :QPoint( p ){}

    MyPoint( int x, int y )
        :QPoint( x, y ){}

    bool operator > ( const MyPoint& another )const
    { 
        if( x() < another.x() )
            return false;

        if( x() > another.x() )
            return true;

        if( y() < another.y() )
            return false;

        if( y() > another.y() )
            return true;

        return false;
    }

    bool operator ==( const MyPoint& another )const
    {
        return x() == another.x() && y() == another.y();
    }

    bool operator < ( const MyPoint& another )const
    {
        if( *this == another )
            return false;

        return !( *this > another );
    }

    QPoint getPoint()const
    {
        return QPoint( x(), y() );
    }
};

//-------------------------------------------------------

struct CommandData
{
    CommandData():flag( -1, -1 ){}

    QPoint flag;

};

//-------------------------------------------------------

struct MapOperationsImpl
{
    Map map;

    QMap< QPair< MyPoint, MyPoint >, QPoint > nearestPointMap;
    QMap< QPair< MyPoint, MyPoint >, int >    pathMap;

    CommandData command1;
    CommandData command2;

    void recalculatePaths();

    inline CommandData& command( int side ){ return side == 1 ? command1 : command2; }

private:    
    void inline calculatePath( const MyPoint& start );
    void inline pushIfOk( const MyPoint& where, const int newValue, QQueue< MyPoint >& queue, DualArray< int >& values, const MyPoint& start, const MyPoint& current);
};

//-------------------------------------------------------

MapOperations::MapOperations( const Map& map )
:m_impl( new MapOperationsImpl() )
{
    m_impl->map = map;

    m_impl->recalculatePaths();
}

//-------------------------------------------------------

MapOperations::~MapOperations()
{

}

//-------------------------------------------------------

void MapOperationsImpl::recalculatePaths()
{
    for( int x = 0; x < map.width(); x++ )
        for( int y = 0; y < map.height(); y++ )
        {
            QPoint begin( x, y );
    
            calculatePath( begin );
        }
}

//-------------------------------------------------------

void MapOperationsImpl::calculatePath( const MyPoint& start )
{
    QQueue< MyPoint > queue;
    DualArray< int > result( map.width(), map.height(), -1 );

    queue.enqueue( start );
    result.setObjectAt( start.x(), start.y(), 0 );
    
    while( queue.size() != 0 )
    {
        MyPoint current = queue.dequeue();

        int x = current.x();
        int y = current.y();

        int newValue = result.objectAt( x, y ) + 1;

        pushIfOk( MyPoint( x - 1, y ), newValue, queue, result, start, current );
        pushIfOk( MyPoint( x + 1, y ), newValue, queue, result, start, current );
        pushIfOk( MyPoint( x, y - 1 ), newValue, queue, result, start, current );
        pushIfOk( MyPoint( x, y + 1 ), newValue, queue, result, start, current );
    }
}

//-------------------------------------------------------

void MapOperationsImpl::pushIfOk( const MyPoint& where, const int newValue, QQueue< MyPoint >& queue, DualArray< int >& values, const MyPoint& start, const MyPoint& current )
{
    if( !PolkApp::canComeIn( map.objectAt( where ) ) )
        return;

    if( !values.isInRange( where ) )
        return;

    if( values.objectAt( where ) != -1 )
        return;

    values.setObjectAt( where, newValue );

    queue.enqueue( where );

    QPair< MyPoint, MyPoint > newItem( where, start );

    pathMap.insert( newItem, newValue );
    nearestPointMap.insert( newItem, current );
}

//-------------------------------------------------------

MovementDirection MapOperations::nearestPointFromPath( const QPoint& start, const QPoint& stop )const
{
    MapObject startObject = m_impl->map.objectAt( start );

    if( !PolkApp::canComeIn( startObject ) )
        return MovementDirection();

    return MovementDirection::createDirection( start, m_impl->nearestPointMap[ QPair< MyPoint, MyPoint > ( start, stop ) ] );
}

//-------------------------------------------------------

QPoint MapOperations::flagPoint( int side )const
{    
    MapObject flagObject = side == 1 ? FirstCommandFlag : SecondCommandFlag;

    if( m_impl->command( side ).flag.x() == -1 || m_impl->command( side ).flag.y() == -1 )
    {
        for( int x = 0; x < m_impl->map.width(); x++ )
            for( int y = 0; y < m_impl->map.height(); y++ )
            {
                if( m_impl->map.objectAt( x, y ) == flagObject )
                {
                    m_impl->command( side ).flag = QPoint( x, y );
                }
            }
    }

    return  m_impl->command( side ).flag;    
}

//-------------------------------------------------------

