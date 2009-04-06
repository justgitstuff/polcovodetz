
#ifndef  __MAP_
#define  __MAP_

#include <Core/Common/DualArray.h>

//-------------------------------------------------------

class QIODevice;

//-------------------------------------------------------

class Map
{
public:
    enum MapObject { Empty = 0, 
                     Grassland, Brick, Water, Stone, 
                     FirstCommandBox, SecondCommandBox,
                     Count };
    
    Map();
    Map( const int width, const int height );
    ~Map();

    MapObject objectAt( const int x, const int y )const; //ассимптотика O(1)

    void setObjectAt( const int x, const int y, const MapObject );

    int width()const{ return m_values.width(); }
    int height()const{ return m_values.height(); }

    bool loadFromFile( QIODevice& );

private:
    typedef DualArray< MapObject > MapArray; 
    MapArray m_values;
};


//-------------------------------------------------------

#endif //__MAP_

//-------------------------------------------------------
