
//-------------------------------------------------------

#ifndef  __DUAL_ARRAY_
#define  __DUAL_ARRAY_

//-------------------------------------------------------

#include <QPoint>
#include <QVector>

//-------------------------------------------------------

template< class T >
class DualArray
{
public:
    DualArray(){ init( 0, 0, QVector< T >() ); }
    DualArray( const int width, const int height, const T& value );
    DualArray( const int width, const int height, const QVector< T >& values ){ init( width, height, values ); }
    virtual ~DualArray(){}

    T     objectAt( const int x, const int y )const;
    T     objectAt( const QPoint& p )const{ return objectAt( p.x(), p.y() ); }

    void  setObjectAt( const int x, const int y, const T& value );
    void  setObjectAt( const QPoint& p, const T& value ){ return setObjectAt( p.x(), p.y(), value ); }

    int   width()const{ return m_width; }
    int   height()const{ return m_height; }

    bool  isInRange( int x, int y ){ return x >= 0 && y >= 0 && x < m_width && y < m_height; }
    bool  isInRange( const QPoint& p ){ return isInRange( p.x(), p.y() ); }

private:
    void init( const int width, const int height, const QVector< T >& values );

    QVector< T > m_values;

    int  m_width;
    int  m_height;
};

//-------------------------------------------------------

template< class T >
DualArray< T >::DualArray( const int width, const int height, const T& value )
{
    init( width, height, QVector< T >( width * height, value ) ); 

}

//-------------------------------------------------------

template< class T >
void DualArray< T >::init( const int width, const int height,  const QVector< T >& values )
{
    m_values = values;

    m_width = width; 
    m_height = height;
}

//-------------------------------------------------------

template< class T >
T DualArray< T >::objectAt( const int x, const int y )const
{
    return m_values[ x + y * m_height ]; 
}

//-------------------------------------------------------

template< class T >
void DualArray< T >::setObjectAt( const int x, const int y, const T& value )
{
    if( !isInRange( x, y ) )
        return;

    m_values[ x + m_height * y ] = value;
}

//-------------------------------------------------------

#endif //__DUAL_ARRAY_

