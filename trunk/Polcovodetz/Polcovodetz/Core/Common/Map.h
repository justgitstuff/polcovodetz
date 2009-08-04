
#ifndef  __MAP_
#define  __MAP_

//-------------------------------------------------------

#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct MapImpl;
class  QIODevice;

//-------------------------------------------------------

enum MapObject { Empty = 0, 
                 Grassland, Brick, Water, Stone, 
                 FirstCommandBox, SecondCommandBox,
                 Count };
    
class Map
{
public:
    Map();
    Map( const int width, const int height );
    ~Map();

    MapObject objectAt( const int x, const int y )const; //ассимптотика O(1)

    void setObjectAt( const int x, const int y, const MapObject );

    int width()const;
    int height()const;

    int objectCount( const MapObject& obj )const;

    bool loadFromFile( QIODevice& );

private:
    boost::shared_ptr< MapImpl > m_impl;          
};


//-------------------------------------------------------

#endif //__MAP_

//-------------------------------------------------------
