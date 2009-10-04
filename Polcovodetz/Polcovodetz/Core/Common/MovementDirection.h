#ifndef MOVEMENTDIRECTION_H
#define MOVEMENTDIRECTION_H

//-------------------------------------------------------

#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct MovementDirectionImpl;

class QPoint;

//-------------------------------------------------------

class MovementDirection
{
public:

    MovementDirection( int angle = -1 );
    ~MovementDirection(){};

    bool isNull()const;

    int  direction()const;
    void setDirection( int direction );

    static const int Top   = 0;
    static const int Right = 90;
    static const int Down  = 180;
    static const int Left  = 270;

    static MovementDirection createDirection( const QPoint& from, const QPoint& to );
private:
    boost::shared_ptr< MovementDirectionImpl > m_impl;
};

//-------------------------------------------------------

#endif // MOVEMENTDIRECTION_H

//-------------------------------------------------------

