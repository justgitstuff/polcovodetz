
#include <Map.h>

#include <DualArray.h>

#include <QIODevice>
#include <QMap>
#include <QPoint>

//--------------------------------------------------------------------------

typedef DualArray< MapObject > MapArray; 

//--------------------------------------------------------------------------

struct MapImpl
{
    MapArray values;

    QMap< MapObject, int > objectCounts;

    QVector< QPoint > firstCommandBoxes;
    QVector< QPoint > secondCommandBoxes;
};

//--------------------------------------------------------------------------

Map::Map( const int width, const int height )
:m_impl( new MapImpl() )
{
    m_impl->values = MapArray( width, height, Empty );
}

//--------------------------------------------------------------------------

Map::Map()
:m_impl( new MapImpl() )
{ }

//--------------------------------------------------------------------------

Map::~Map()
{ }

//--------------------------------------------------------------------------

MapObject Map::objectAt( const QPoint& where ) const 
{
    return objectAt( where.x(), where.y() );
}

//--------------------------------------------------------------------------

MapObject Map::objectAt( const int x,  const int y ) const 
{
    if ( !m_impl->values.isInRange( x, y ) )
        return Empty;

    return m_impl->values.objectAt( x, y );
} 

//--------------------------------------------------------------------------

void Map::setObjectAt( const int x, const int y, const MapObject obj )
{
    m_impl->values.setObjectAt( x, y, obj );
}

//--------------------------------------------------------------------------

bool Map::loadFromFile( QIODevice& dev )
{
    QByteArray tmpArr = dev.read( 2 );

    if( tmpArr.length() < 2 )
        return false;

    int w = tmpArr[ 0 ];
    int h = tmpArr[ 1 ];

    tmpArr = dev.read( w * h );

    if( tmpArr.length() < w * h )
        return false;

    MapArray newMap( w, h, Empty );

    for( int wid = 0; wid < w; wid++ )
    {
        for( int hey = 0; hey < h; hey++ )
        {
            int value = tmpArr[ hey * h + wid ];

            if( value > Count )
                return false;

            newMap.setObjectAt( wid, hey, (MapObject)value );

            m_impl->objectCounts[ (MapObject)value ]++;

        }
    }

    m_impl->values = newMap;

    m_impl->firstCommandBoxes.clear();
    m_impl->secondCommandBoxes.clear();

    for( int x = 0; x < w; x++ )
    {
        for( int y = 0; y < h; y++ )
        {
            switch( newMap.objectAt( x, y ) )
            {
            case ::FirstCommandBox :
                m_impl->firstCommandBoxes.append( QPoint( x, y ) );
                break;
            case ::SecondCommandBox :
                m_impl->secondCommandBoxes.append( QPoint( x, y ) );
                break;
            }
        }
    }

    return true;
}

//--------------------------------------------------------------------------

int Map::objectCount( const MapObject& obj )const
{
    return m_impl->objectCounts[ obj ];
}

//--------------------------------------------------------------------------

int Map::width()const
{ 
    return m_impl->values.width(); 
}

//--------------------------------------------------------------------------

int Map::height()const
{ 
    return m_impl->values.height(); 
}

//--------------------------------------------------------------------------

QPoint Map::getRandomTankPlace( const int side )const
{
    for( int x = 0; x < m_impl->values.width(); x++ )
    {
        for( int y = 0; y < m_impl->values.height(); y++ )
        {
            MapObject obj = m_impl->values.objectAt( x, y );

            if( obj == FirstCommandBox && side == 1 )
                return QPoint( x, y );

            if( obj == SecondCommandBox && side == 2 )
                return QPoint( x, y );
        }
    }

    return QPoint( -1, -1 );
}

//--------------------------------------------------------------------------

QPoint Map::getTankPlace( const int side, const int number )const
{
    QVector< QPoint >& array = side == 1 ? m_impl->firstCommandBoxes : m_impl->secondCommandBoxes;

    if( number >= array.size() || number < 0 )
        return QPoint( -1, -1 );

    return array[ number ];
}

//--------------------------------------------------------------------------

int Map::tankPlaceCount( const int side )const
{
    QVector< QPoint >& array = side == 1 ? m_impl->firstCommandBoxes : m_impl->secondCommandBoxes;

    return array.size();
}

//--------------------------------------------------------------------------

