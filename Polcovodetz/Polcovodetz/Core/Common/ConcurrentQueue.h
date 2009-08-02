
#ifndef  __CONCURRENT_QUEUE
#define  __CONCURRENT_QUEUE

//-------------------------------------------------------

#include <QMutex>
#include <QMutexLocker>
#include <QVector>

//-------------------------------------------------------

/**
    Многопоточная очередь

    ToDo: 
        1) Сделать LockFree.
        2) Сделать возможность уменьшаться.
*/
template< class T >
class ConcurrentQueue
{
public:
    ConcurrentQueue();

    bool push( const T& );
    T    pop();

    bool isEmpty()const;
    int  size()const;
    bool clear();

private:
    QVector< T > values;
    QMutex       mutex;
    int head;
    int count;
};

//-------------------------------------------------------

template< class T >
ConcurrentQueue< T >::ConcurrentQueue()
:head( 0 ), count( 0 ), values(), mutex()
{
}

//-------------------------------------------------------

template< class T >
bool ConcurrentQueue< T >::push( const T& newElement )
{
    QMutexLocker locker( &mutex );
    if( count == values.count() )
    {
        QVector< T > newValues( ( count + 1 )* 2 );

        for( int i = 0; i < count; i++ )
        {
            newValues[ i ] = values[ ( i + head ) % count ];            
        }

        values = newValues;
    }

    values[ ( head + count ) % values.count() ] = newElement;

    count++;

    return true;
}

//-------------------------------------------------------

template< class T >
T ConcurrentQueue< T >::pop()
{
    QMutexLocker locker( &mutex );

    if( count == 0 )
        return T();

    T result = values[ head ];

    head++;
    head %= values.count();
    count--;

    return result;
}

//-------------------------------------------------------

template< class T >
int ConcurrentQueue< T >::size()const
{
    QMutexLocker locker( &mutex );

    return count;
}

//-------------------------------------------------------

template< class T >
bool ConcurrentQueue< T >::isEmpty()const
{
    return size() == 0;
}

//-------------------------------------------------------

template< class T >
bool ConcurrentQueue< T >::clear()
{
    QMutexLocker locker( &mutex );

    values.clear();
    head = 0;
    count = 0;
}

//-------------------------------------------------------
#endif //__CONCURRENT_QUEUE
