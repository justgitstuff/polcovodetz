
//-------------------------------------------------------

#include <Core/MultiThreading/CommandThread.h>

#include <Core/BaseClasses/ICommandController.h>
#include <Core/BaseClasses/IGroupController.h>
#include <Core/BaseClasses/IObjectController.h>
#include <Core/BaseClasses/Messages.h>
#include <Core/Common/ConcurrentQueue.h>
#include <Core/Drivers/SimpleCommandDrivers.h>
#include <Core/Drivers/SimpleGroupDrivers.h>
#include <Core/Drivers/SimpleObjectDrivers.h>
#include <Core/LibraryLoader.h>
#include <Core/PolkApp.h>

#include <QApplication>
#include <QMap>
#include <QVector>

//-------------------------------------------------------

namespace
{
    enum MsgElement
    {
        None, Core, CommandController, GroupController, ObjectController
    };

    struct Action
    {
        MsgElement                           who;
        MsgElement                           toWhom;
        boost::shared_ptr< AbstractMessage > message;        

        Action():toWhom( None ), who( None ), message(){};

    };

    typedef boost::shared_ptr< Action > ActionPtr;

}

//-------------------------------------------------------

struct CommandThreadImpl
{
    CommandThreadImpl():ccID( 0 ), driverStorage(){}
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

    QMap< qint64, boost::shared_ptr< SimpleObjectOutputDriver > > objectsMap;

    ConcurrentQueue< ActionPtr >   actionsQueue;

    bool paused;

    int side;
};

//-------------------------------------------------------

CommandThread::CommandThread( const int side )
:QThread(), m_impl( new CommandThreadImpl() )
{
    m_impl->side = side;
}

//-------------------------------------------------------

bool CommandThread::start()
{
    m_impl->paused = false;

    QThread::start();

    return true;
}

//-------------------------------------------------------

bool CommandThread::pause()
{    
    m_impl->paused = true;

    return true;
}

//-------------------------------------------------------

void CommandThread::run()
{
    connectDrivers();
    initDrivers();

    while( 1 )
    {        
        if( m_impl->paused )
        {
            QThread::sleep( 1000 );

            continue;
        }

        sendInnerMessages();

        qApp->processEvents();

        QThread::sleep( 100 );
    }
    return;
}

//-------------------------------------------------------

void CommandThread::sendInnerMessages( const int maxMessages )
{
    for( int msgCount = 0; msgCount < maxMessages; msgCount++ )
    {
        ActionPtr action = m_impl->actionsQueue.pop();

        if( action.get() == 0 || ( action->toWhom == None && action->who == None ) )
        {
            return;
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

bool CommandThread::registerCommandController( const int libraryID )
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
int CommandThread::registerGroupController( const int libraryID )
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
int CommandThread::registerObjectController( const int libraryID, const int gID, const int pObject )
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

int CommandThread::commandController()
{
    return m_impl->ccID;
}

//-------------------------------------------------------

IDEnumeration CommandThread::groupControllers()
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
IDEnumeration CommandThread::objectControllers(const int groupID )
{
    return IDEnumeration( m_impl->ocIDs[ groupID ] );
}

//-------------------------------------------------------

int CommandThread::commandControllerLibId()
{
    return m_impl->ccID;
}

//-------------------------------------------------------

int CommandThread::groupControllerLibId( const int groupID )
{
    return m_impl->gcIDs[ groupID ];
}

//-------------------------------------------------------

int CommandThread::objectControllerLibId( const int objectID )
{
    return m_impl->ocLibs[ objectID ];
}

//-------------------------------------------------------

int CommandThread::objectControllerPObject( const int objectID )
{
    return m_impl->ocPObjs[ objectID ];
}

//-------------------------------------------------------

bool CommandThread::connectDrivers()
{
    m_impl->cController.reset( libLoader.loadCommandController( m_impl->ccID ) );

    SimpleCommandInputDriver*  cid = new SimpleCommandInputDriver();
    SimpleCommandOutputDriver* cod = new SimpleCommandOutputDriver();    

    cid->init( m_impl->cController, *this );
    cod->init( m_impl->cController );

    m_impl->ciDriver.reset( cid );
    m_impl->coDriver.reset( cod );

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

            boost::shared_ptr< SimpleObjectInputDriver >  oid ( new SimpleObjectInputDriver() );
            boost::shared_ptr< SimpleObjectOutputDriver > ood ( new SimpleObjectOutputDriver( this ) );
            
            oid->init( oc );
            ood->init( oc );

            god->dConnect( oid );
            oid->dConnect( god );

            oc->init( oid.get(), ood.get() );

            PtrPObject newObj = pApp.getNewObject( m_impl->side, 1 );
            ood->dConnect( newObj );

            m_impl->objectsMap[ newObj->objectID() ] = ood;

            m_impl->oControllers[ id ].append( oc );

            m_impl->driverStorage.append( oid );
            m_impl->driverStorage.append( ood );
        }

        m_impl->gControllers[ id ] = gc;        
    }

    //cid->sendMessage( CommandInputMessage( CommandInputMessage::GameStarted ) );

    return true;
}

//-------------------------------------------------------

bool CommandThread::initDrivers()
{
    m_impl->cController->init( m_impl->ciDriver.get(), m_impl->coDriver.get() );

    return true;
}

//-------------------------------------------------------

int CommandThread::sendCoreCommandMessage( CoreCommandMessage* message )
{
    ActionPtr newAction( new Action() );
    newAction->toWhom = CommandController;
    newAction->who = Core;
    newAction->message.reset( message );
    
    if( m_impl->actionsQueue.push( newAction ) )
        return 0;

    return 1;
}

//-------------------------------------------------------

bool CommandThread::setSpeed( const PtrPObject& object, const QPoint& persent )
{
    return pApp.setSpeed( object, persent );
}

//-------------------------------------------------------

bool CommandThread::setRotation( const PtrPObject& object, int angle )
{
    return pApp.setRotation( object, angle );
}

//-------------------------------------------------------

void CommandThread::disposeObject( const PtrPObject& object )
{
    qint64 id = object->objectID();

    boost::shared_ptr< SimpleObjectOutputDriver > outDriver = m_impl->objectsMap[ id ];

    if( outDriver.get() )
        outDriver->dConnect( PtrPObject() );

    m_impl->objectsMap.remove( id );
}

//-------------------------------------------------------
/*
void CommandThread::getNewObject( const int side, const int rtti )
{
    pApp.getNetObject
}
*/
//-------------------------------------------------------

//-------------------------------------------------------

void CommandThread::makeRocket( const PtrPObject& who )
{
    return pApp.makeRocket( who );
}

//-------------------------------------------------------
