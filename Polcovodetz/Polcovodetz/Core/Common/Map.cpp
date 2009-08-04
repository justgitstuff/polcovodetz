
#include <Core/Common/Map.h>

#include <Core/Common/DualArray.h>

#include <QIODevice>
#include <QMap>

//--------------------------------------------------------------------------

typedef DualArray< MapObject > MapArray; 

//--------------------------------------------------------------------------

struct MapImpl
{
    MapArray values;

    QMap< MapObject, int > objectCounts;
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

MapObject Map::objectAt( const int x,  const int y ) const 
{
    if ( x < 0 || y < 0 || x >= m_impl->values.width() || y >= m_impl->values.height() )
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

