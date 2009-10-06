
//-------------------------------------------------------

#include <Core/StateManagers/PositionManager.h>

#include <Core/MultiThreading/CommandState.h>
#include <Core/PolkApp.h>

#include <Messages.h>

#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QPoint>
#include <QSize>

//-------------------------------------------------------

struct PositionManagerImpl
{
    typedef QMap< qint64, PtrPObject > ObjectMap;
    typedef QMap< qint64, QPoint >     PositionMap;

    QMutex mutex;

    ObjectMap   objects;
    PositionMap positions;

    CommandState* command1;
    CommandState* command2;

    void sendMessage( const PtrPObject& obj, const boost::shared_ptr< AbstractMessage >& msg )
    {
        ( obj->side() == 1 ? command1 : command2 )->sendMessage( msg );
    }
};

//-------------------------------------------------------

QPoint calculateComeInPosition( const QPoint& position, const QPoint& speed, const QSize& size )
{
    QPoint watchPoint = position;
    
    if( speed.x() > 0 )
        watchPoint.setX( watchPoint.x() + size.width() );
    
    if( speed.y() > 0 )
        watchPoint.setY( watchPoint.y() + size.height() );

    watchPoint.setX( watchPoint.x() / PolkApp::SQUARE_SIZE );
    watchPoint.setY( watchPoint.y() / PolkApp::SQUARE_SIZE );

    return watchPoint;
}

//-------------------------------------------------------

QPoint calculateComeOutPosition( const QPoint& position, const QPoint& speed, const QSize& size )
{
    QPoint newSpeed = speed;

    newSpeed *= -1;

    return calculateComeInPosition( position, newSpeed, size );
}

//-------------------------------------------------------

PositionManager::PositionManager( CommandState* command1, CommandState* command2 )
:m_impl( new PositionManagerImpl() )
{
    m_impl->command1 = command1;
    m_impl->command2 = command2;
}

//-------------------------------------------------------

PositionManager::~PositionManager()
{

}

//-------------------------------------------------------

void PositionManager::addObject( const PtrPObject& obj )
{
    QMutexLocker( &m_impl->mutex );

    qint64 id = obj->objectID();

    m_impl->positions.insert( id, obj->position() );

    m_impl->objects.insert( id, obj );
}

//-------------------------------------------------------

void PositionManager::deleteObject( qint64 id )
{
    QMutexLocker( &m_impl->mutex );

    m_impl->objects.remove( id );
    m_impl->positions.remove( id );
}

//-------------------------------------------------------

void PositionManager::checkObjects()
{   
    QMutexLocker( &m_impl->mutex );

    PositionManagerImpl::PositionMap& positions = m_impl->positions;
    PositionManagerImpl::ObjectMap&   objects   = m_impl->objects;

    for( PositionManagerImpl::ObjectMap::ConstIterator iter = objects.constBegin();
         iter != objects.constEnd();
         iter++ )
    {
        PtrPObject val = iter.value();

        QPoint newPosition = val->position();
        QPoint oldPosition = positions[ iter.key() ];

        positions[ iter.key() ] = newPosition;

        QPoint speed = val->speed();
        QSize  size  = val->boundSize();

        QPoint oldComeInSquare = calculateComeInPosition( oldPosition, speed, size );
        QPoint newComeInSquare = calculateComeInPosition( newPosition, speed, size );

        QPoint oldComeOutSquare = calculateComeOutPosition( oldPosition, speed, size );
        QPoint newComeOutSquare = calculateComeOutPosition( newPosition, speed, size );

        if( oldComeInSquare != newComeInSquare )
        {            
            CoreObjectMessage* msg = new CoreObjectMessage( val->objectID() );

            msg->type = CoreObjectMessage::SquareInChanged;

            m_impl->sendMessage( val, boost::shared_ptr< AbstractMessage >( msg ) );
        }

        if( oldComeOutSquare != newComeOutSquare )
        {
            CoreObjectMessage* msg = new CoreObjectMessage( val->objectID() );

            msg->type = CoreObjectMessage::SquareOutChanged;

            m_impl->sendMessage( val, boost::shared_ptr< AbstractMessage >( msg ) );
        }
    }
}

//-------------------------------------------------------


