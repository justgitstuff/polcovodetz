
#include <Core/Common/Map.h>

#include <QIODevice>

//--------------------------------------------------------------------------

Map::Map( const int width, const int height )
:m_values( width, height, Empty )
{
}

//--------------------------------------------------------------------------

Map::Map()
:m_values()
{ }

//--------------------------------------------------------------------------

Map::~Map()
{ }

//--------------------------------------------------------------------------

Map::MapObject Map::objectAt( const int x,  const int y ) const 
{
    if ( x < 0 || y < 0 || x >= m_values.width() || y >= m_values.height() )
        return Empty;

    return m_values.objectAt( x, y );
} 

//--------------------------------------------------------------------------

void Map::setObjectAt( const int x, const int y, const MapObject obj )
{
    m_values.setObjectAt( x, y, obj );
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
        }
    }

    m_values = newMap;

    return true;
}

//--------------------------------------------------------------------------

