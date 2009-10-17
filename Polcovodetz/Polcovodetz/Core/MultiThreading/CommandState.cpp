
#include <Core/MultiThreading/CommandState.h>

#include <Core/BaseClasses/ICommandController.h>
#include <Core/BaseClasses/IGroupController.h>
#include <Core/BaseClasses/IObjectController.h>
#include <Core/BaseClasses/Messages.h>
#include <Core/Calculations/DriverHelper.h>
#include <Core/Common/ConcurrentQueue.h>
#include <Core/Drivers/SimpleCommandDrivers.h>
#include <Core/Drivers/SimpleGroupDrivers.h>
#include <Core/Drivers/SimpleObjectDrivers.h>
#include <Core/LibraryLoader.h>
#include <Core/PolkApp.h>

#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QSize>
#include <QVector>

//-------------------------------------------------------

struct CommandStateImpl
{
    typedef QMap< qint64, SimpleObjectDriver* > ObjectDriversMap;

    typedef QMap< qint64, boost::shared_ptr< IAbstractDriver > > DriversMap;

    typedef QMap< SimpleObjectDriver*, QPoint > PositionMap;
    typedef QMap< SimpleObjectDriver*, int >    CountMap;

    CommandStateImpl():ccID( 0 ), driverStorage(){}
    //IDs
    int                          ccID; //command controller library id
    QMap< int, int >             gcIDs;//Map: group controller id to his library id;
    QMap< int, IDEnumeration >   ocIDs;//Map: group controller id to object ids

    QMap< int, int >             ocLibs;//Map: object controller id to his library id;

    QMap< int, int >             ocPObjs;//Map: object controller id to his PObject id;

    QVector< boost::shared_ptr< IAbstractDriver > >      driverStorage;

    boost::shared_ptr< ICommandInputDriver >             ciDriver;
    boost::shared_ptr< ICommandOutputDriver >            coDriver;

    boost::shared_ptr< ICommandController >              cController;

    QMap< int, boost::shared_ptr< IGroupController > >   gControllers;//map: group controller id to his controller
    QMap< int, QVector< boost::shared_ptr< IObjectController > > >  oControllers;//map: group controller id to his controller
    
    ObjectDriversMap                                     oDrivers; //map: PtrPObject id to his driver
    PositionMap                                          positions;//map: connected objects to his positions
    CountMap                                             positionCount;//map: connected objects to count of iterations, where he doesn`t change position

    ObjectDriversMap objectsMap;
    DriversMap driversMap;

    ConcurrentQueue< ActionPtr >   actionsQueue;

    bool paused;

    QMutex mutex;

    int side;

    boost::shared_ptr< DriverHelper > driverHelper;
};

//-------------------------------------------------------

inline QPoint calculatePosition( SimpleObjectDriver* driver )
{
    if( driver->pObject() )
    {
        PtrPObject obj = driver->ptrPObject();

        QPoint where = obj->position();
        QSize  size  = obj->boundSize();

        where.setX( where.x() - size.width() );
        where.setY( where.y() - size.height() );

        where /= PolkApp::SQUARE_SIZE;

        return where;
    }

    return QPoint( -1, -1 );
}

//-------------------------------------------------------

CommandState::CommandState( const int side )
:m_impl( new CommandStateImpl() ) 
{
    m_impl->side = side;
}

//-------------------------------------------------------

int CommandState::side()const
{
    return m_impl->side;
}

//-------------------------------------------------------
void CommandState::sendInnerMessages( const int maxMessages )
{
    for( int msgCount = 0; !m_impl->actionsQueue.isEmpty() && msgCount < maxMessages; msgCount++ )
    {
        ActionPtr action = m_impl->actionsQueue.pop();

        if( action.get() == 0 )
        {
            return;
        }

        switch( action->message->rtti() )
        {
        case CoreCommandMessage::RTTI:
            {
                CoreCommandMessage* msg = ( CoreCommandMessage* )action->message.get();

                m_impl->ciDriver->sendMessage( msg );

                break;
            }
        case CoreGroupMessage::RTTI:
            {
                break;
            }
        case CoreObjectMessage::RTTI:
            {
                CoreObjectMessage* msg = ( CoreObjectMessage* )action->message.get();

                qint64 id = msg->id();

                if( !m_impl->oDrivers.contains( id ) )
                    continue;
 
                m_impl->oDrivers[ id ]->message( msg );
                
                break;
            }
        case CommandGroupMessage::RTTI:
            {
                break;
            }
        case CommandObjectMessage::RTTI:
            {
                break;
            }
        case GroupCommandMessage::RTTI:
            {
                break;
            }
        case GroupObjectMessage::RTTI:
            {
                break;
            }
        case ObjectGroupMessage::RTTI:
            {
                break;
            }
        case ObjectCommandMessage::RTTI:
            {
                break;
            }
        }

        switch( action->who )
        {
        case Core:
            {
                switch( action->toWhom )
                {
                case CommandController:
                    {
                        CoreCommandMessage* msg = ( CoreCommandMessage* )action->message.get();

                        m_impl->ciDriver->sendMessage( msg );

                        break;
                    }
                }
            }
        }
        
    }
}

//-------------------------------------------------------

bool CommandState::registerCommandController( const int libraryID )
{
    if( m_impl->ccID != 0 )
        return false;

    m_impl->ccID = libraryID;

    return true;
}


//-------------------------------------------------------
/**
    Регистрирует контроллер группы. 
    libraryID - id библиотеки, откуда загружать контроллер

    ToDo: добавить проверку библиотеки!
*/
int CommandState::registerGroupController( const int libraryID )
{
    static int GROUP_ID = 0;
    int groupID = ++GROUP_ID;
    m_impl->gcIDs.insert( groupID, libraryID );

    return groupID;
}

//-------------------------------------------------------
/**
    Регистрирует контроллер объекта. 
    libraryID - id библиотеки, откуда загружать контроллер
    gID - ID группового контроллера
    pObject - объект, которым будет управлять контроллер

    ToDo: добавить проверку библиотеки!
*/
int CommandState::registerObjectController( const int libraryID, const int gID, const int pObject )
{
    if( pObject == 0 )
        return -1;

    if( !m_impl->gcIDs.contains( gID ) )
        return -1;

    static int OBJECT_ID = 0;
    int objectID = ++OBJECT_ID;

    m_impl->ocIDs[ gID ].append( objectID );
    m_impl->ocLibs.insert( objectID, libraryID );
    m_impl->ocPObjs.insert( objectID, pObject );

    return objectID;
}

//-------------------------------------------------------

int CommandState::commandController()
{
    return m_impl->ccID;
}

//-------------------------------------------------------

IDEnumeration CommandState::groupControllers()
{
    IDEnumeration res;
    
    for( QMap< int, int >::const_iterator iter = m_impl->gcIDs.constBegin();
         iter != m_impl->gcIDs.constEnd();
         iter++ )
    {
        res.append( iter.key() );
    }
    return res;
}

//-------------------------------------------------------
/**
    Выводит список объектов для контроллера группы
    side - играющая сторона, для которой выводится список объектов
    groupID - id группы, у которой прикреплены объекты
*/
IDEnumeration CommandState::objectControllers(const int groupID )
{
    return IDEnumeration( m_impl->ocIDs[ groupID ] );
}

//-------------------------------------------------------

int CommandState::commandControllerLibId()
{
    return m_impl->ccID;
}

//-------------------------------------------------------

int CommandState::groupControllerLibId( const int groupID )
{
    return m_impl->gcIDs[ groupID ];
}

//-------------------------------------------------------

int CommandState::objectControllerLibId( const int objectID )
{
    return m_impl->ocLibs[ objectID ];
}

//-------------------------------------------------------

int CommandState::objectControllerPObject( const int objectID )
{
    return m_impl->ocPObjs[ objectID ];
}

//-------------------------------------------------------

bool CommandState::connectDrivers()
{
    m_impl->driverHelper.reset( new DriverHelper( pApp.map() ) );

    m_impl->cController.reset( libLoader.loadCommandController( m_impl->ccID ) );

    SimpleCommandInputDriver*  cid = new SimpleCommandInputDriver();
    SimpleCommandOutputDriver* cod = new SimpleCommandOutputDriver( this );    

    cid->init( m_impl->cController, *this );
    cod->init();

    m_impl->ciDriver.reset( cid );
    m_impl->coDriver.reset( cod );

    m_impl->driversMap.insert( cid->driverID(), m_impl->ciDriver );
    m_impl->driversMap.insert( cod->driverID(), m_impl->coDriver );

    m_impl->gControllers.clear();

    m_impl->cController->init( cid, cod );

    for( QMap< int, int >::ConstIterator iter = m_impl->gcIDs.constBegin();
        iter != m_impl->gcIDs.constEnd();
        iter++ )
    {
        int id = iter.key();

        boost::shared_ptr< IGroupController > gc( libLoader.loadGroupController( iter.value() ) );

        boost::shared_ptr< SimpleGroupInputDriver >  gid ( new SimpleGroupInputDriver() );
        boost::shared_ptr< SimpleGroupOutputDriver > god ( new SimpleGroupOutputDriver() );
        
        m_impl->driversMap.insert( gid->driverID(), gid );
        m_impl->driversMap.insert( god->driverID(), god );

        gid->init( gc );
        god->init( gc );

        gc->init( gid.get(), god.get() );

        cod->dConnect( gid );
        gid->dConnect( m_impl->coDriver );

        QVector< int > oIDs = m_impl->ocIDs[ id ];

        m_impl->driverStorage.append( gid );
        m_impl->driverStorage.append( god );

        m_impl->oControllers[ id ].clear();

        for( IDEnumeration::const_iterator iter = oIDs.constBegin();
             iter != oIDs.constEnd();
             iter++ )
        {
            boost::shared_ptr< IObjectController > oc( libLoader.loadObjectController( m_impl->ocLibs[ *iter ] ) );

            boost::shared_ptr< SimpleObjectDriver > od ( new SimpleObjectDriver( this ) );

            m_impl->driversMap.insert( od->driverID(), od );
            
            od->init( oc );

            oc->init( od.get() );

            m_impl->driverStorage.append( od );
    
            m_impl->oControllers[ id ].append( oc );

            createConnectedObject( 1, od->driverID() );
        }

        m_impl->gControllers[ id ] = gc;        
    }
    /*
    for( CommandStateImpl::DriversMap::ConstIterator iter = m_impl->driversMap.constBegin();
         iter != m_impl->driversMap.constEnd();
         iter++ )
    {
        CoreObjectMessage* msg = new CoreObjectMessage( iter.value()->
    }*/

    return true;
}

//-------------------------------------------------------

int CommandState::sendMessage( boost::shared_ptr< AbstractMessage > message )
{
    ActionPtr newAction( new Action() );

    newAction->message = message;

    if( m_impl->actionsQueue.push( newAction ) )
        return 0;

    return 2;
}

//-------------------------------------------------------

bool CommandState::setSpeed( const PtrPObject& object, const QPoint& persent )
{
    return pApp.setSpeed( object, persent );
}

//-------------------------------------------------------

bool CommandState::setRotation( const PtrPObject& object, int angle )
{
    return pApp.setRotation( object, angle );
}

//-------------------------------------------------------

void CommandState::disposeObject( const qint64 id )
{
    SimpleObjectDriver* driver = m_impl->objectsMap[ id ];

    if( driver != 0 )
    {
        PtrPObject object = driver->ptrPObject();
        
        if( object.get() == 0 )
            return;

        driver->oConnect( PtrPObject() );

        m_impl->positions.remove( driver );

        CoreCommandMessage* objectCrached = new CoreCommandMessage( CoreCommandMessage::ObjectCrached );

        objectCrached->objectRTTI = object->rtti();
        objectCrached->who = driver->driverID();
        objectCrached->point = object->position();

        sendMessage( boost::shared_ptr< AbstractMessage >( objectCrached ) );
    }

    m_impl->objectsMap.remove( id );
}

//-------------------------------------------------------

void CommandState::makeRocket( const PtrPObject& who )
{
    return pApp.makeRocket( who );
}

//-------------------------------------------------------

void CommandState::createConnectedObject( const int rtti, const qint64 driverID )
{
    QMutexLocker( &m_impl->mutex );

    if( !( m_impl->driversMap.contains( driverID ) ) )
        return;

    IAbstractDriver* aDriver  = m_impl->driversMap[ driverID ].get();

    SimpleObjectDriver* driver = dynamic_cast< SimpleObjectDriver* >( aDriver );

    if( driver == 0 )
        return;

    if( driver->pObject() != 0 )
        return;

    PtrPObject object = pApp.getNewObject( m_impl->side, rtti );

    if( object.get() != 0 )
    {
        qint64 id = object->objectID();

        driver->oConnect( object );

        m_impl->oDrivers.insert( id, driver );

        m_impl->objectsMap.insert( id, driver );

        m_impl->positions[ driver ] = calculatePosition( driver );

        CoreObjectMessage* mes = new CoreObjectMessage( id );

        mes->type = CoreObjectMessage::Recreated;
        mes->point = object->position();

        sendMessage( boost::shared_ptr< CoreObjectMessage >( mes ) );
    }
}

//-------------------------------------------------------

DriverHelper* CommandState::driverHelper()const
{
    return m_impl->driverHelper.get();
}

//-------------------------------------------------------

void CommandState::updatePositions( bool /*sendSignals*/ )
{
    CommandStateImpl::PositionMap& positions = m_impl->positions;
    CommandStateImpl::CountMap& counts = m_impl->positionCount;

    for( CommandStateImpl::PositionMap::ConstIterator iter = positions.constBegin();
         iter != positions.constEnd();
         iter++ )
    {
        QPoint oldVal = iter.value();

        QPoint newVal = calculatePosition( iter.key() );

        SimpleObjectDriver* driver = iter.key();

        positions[ driver ] = newVal;

        int count = counts[ driver ];

        if( count > 33 )
        {
            count = 0;

            CoreObjectMessage* msg = new CoreObjectMessage( driver->pObject()->objectID() );

            msg->type = CoreObjectMessage::Staying;
            msg->point = oldVal;

            sendMessage( boost::shared_ptr< AbstractMessage >( msg ) );
        }

        counts[ driver ] = count + 1;
    }
}

//-------------------------------------------------------

