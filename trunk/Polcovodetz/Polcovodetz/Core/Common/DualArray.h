
//-------------------------------------------------------

#ifndef  __DUAL_ARRAY_
#define  __DUAL_ARRAY_

//-------------------------------------------------------

#include<QVector>

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
    void  setObjectAt(  const int x, const int y, const T& value );

    int   width()const{ return m_width; }
    int   height()const{ return m_height; }

private:
    void init(  const int width, const int height, const QVector< T >& values );

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
void DualArray< T >::setObjectAt( const int width, const int height, const T& value )
{
    if( width * height < m_values.count() )
        m_values[ width + m_height * height ] = value;
}

//-------------------------------------------------------

#endif //__DUAL_ARRAY_

