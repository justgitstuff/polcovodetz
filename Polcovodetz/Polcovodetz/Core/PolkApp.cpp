
//-------------------------------------------------------

#include <Core/PolkApp.h>

#include <Core/BaseClasses/IAbstractDrivers.h>
#include <Core/BaseClasses/Messages.h>
#include <Core/Common/Map.h>
#include <Core/Common/MathUtils.h>
#include <Core/LibraryLoader.h>
#include <Core/MultiThreading/CalcThread.h>
#include <Core/MultiThreading/CommandState.h>
#include <Core/MultiThreading/CommandThread.h>
#include <Core/PObjects/Interfaces/IShootableObject.h>
#include <Core/PObjects/PObject.h>
#include <Core/PObjects/PObjectSharedImpl.h>
#include <Core/WinState.h>

#include <GUI/SpecialControls/PaintArea2D.h>

#include <QtDebug>
#include <QDomDocument>
#include <QFile>
#include <QMap>
#include <QMultiMap>
#include <QMutex>
#include <QPluginLoader>
#include <QPoint>
#include <QSize>
#include <QTextEdit>

//-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!

#include <Core/PObjects/UserObjects/Flying/AbstractRocket.h>
#include <Core/PObjects/UserObjects/Flying/SimpleRocket.h>
#include <Core/PObjects/UserObjects/Moving/AbstractMoveObject.h>
#include <Core/PObjects/UserObjects/Moving/SimpleTank.h>

//-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!

#define GET_STATE( side ) CommandState* st = ( side == 1 ? m_impl->thread1 : m_impl->thread2 ).commandState();

#define GET_THREAD(side) CommandThread& ct = side == 1 ? m_impl->thread1 : m_impl->thread2;

#define GET_LOADED_STATE(side) CommandState* st = side == 1 ? m_impl->command1 : m_impl->command2;

//-------------------------------------------------------

PolkApp pApp;

//-------------------------------------------------------

enum GameState
{
    Stopped,
    Running,
    Paused
};

//-------------------------------------------------------

struct PolkAppImpl
{    
    PolkAppImpl():thread1( 1 ), thread2( 2 ), calcThread(), coreMutex(), state( ::Stopped ) {};
    typedef QMap< long, PtrPObject >           PObjectMap;
    typedef QMap< long, int >                  PObjectSideMap;

    typedef QMap< Qt::Key, IAbstractInputDriver* > KeyMap;
 
    typedef QMultiMap< int, long >             PObjectCoordinateMap;//coordinate to list of ids

    KeyMap                keyMap;

    Map                   map;

    PObjectMap            objectIDs;
    PObjectSideMap        objectSides;

    PObjectCoordinateMap  xCoordinates;       
    PObjectCoordinateMap  yCoordinates;

    GUIControler*         currentView;

    CalcThread            calcThread;

    CommandThread         thread1;
    CommandThread         thread2;

    CommandState*         command1;
    CommandState*         command2;

    PObjectMap            removedObjects;
    QVector< PtrPObject > objectsToDelete;

    QMutex                coreMutex;

    GameState             state;

    WinState              winState;
};

//-------------------------------------------------------

inline MapObject objectAt( int x, int y )
{
    if( y < 0 || x < 0 )
        return Empty;

    int nx = x / PolkApp::SQUARE_SIZE;
    int ny = y / PolkApp::SQUARE_SIZE;

    return pApp.map().objectAt( nx, ny );
};

//-------------------------------------------------------

inline void calculateObject( const PtrPObject& object, int x0, int y0, int& x1, int& y1 )
{
    if( object->onStop() & PObject::Revert )
    {
        x1 = x0;
        y1 = y0;
    }
    if( object->onStop() & PObject::DisposeMyself )
    {
        pApp.disposeObject( object );

        x1 = y1 = -PolkApp::SQUARE_SIZE;
    }
};

//-------------------------------------------------------

PolkApp::PolkApp()
{
    m_impl.reset( new PolkAppImpl() );

    m_impl->currentView  = 0;
}

//-------------------------------------------------------

PolkApp::~PolkApp()
{
}

//-------------------------------------------------------

bool PolkApp::addObjectOnScene( const PtrPObject& obj )
{
    int side = obj->side();
    qint64 id = obj->objectID();

    m_impl->objectSides.insert( id, side );
    m_impl->objectIDs.insert( id, obj );

    emit objectAdded( obj );

    return true; 
}

//-------------------------------------------------------

const Map& PolkApp::map()const
{    
    return m_impl->map;
}

//-------------------------------------------------------

QWidget* PolkApp::currentView()const
{
    if( m_impl->currentView == 0 )
    {
        m_impl->currentView = new GUIControler();

        qRegisterMetaType<PtrPObject>( "PtrPObject" );

        connect( this, SIGNAL( updateVisualState() ),              m_impl->currentView, SLOT( updateObjects() ) );
        connect( this, SIGNAL( objectAdded( const PtrPObject& ) ), m_impl->currentView, SLOT( addPObject( const PtrPObject& ) ) );
        connect( this, SIGNAL( objectDeleted( const qint64 ) ),    m_impl->currentView, SLOT( deleteObject( const qint64 ) ) );
    }

    return new PaintArea2D( m_impl->currentView, NULL );
}

//-------------------------------------------------------

bool PolkApp::reloadMap( const QString& fileName )
{
    QFile file( fileName );

    if( !file.open( QIODevice::ReadOnly ) )
        return false;

    if( !m_impl->map.loadFromFile( file ) )
        return false;

    m_impl->currentView->updateMap();

    return true;
}

//-------------------------------------------------------

bool PolkApp::startGame()
{
    if( m_impl->state == ::Running )
        return false;

    m_impl->state = ::Running;

    if( m_impl->state == ::Paused )
        return m_impl->thread1.start() && m_impl->thread2.start() && m_impl->calcThread.start();

    bool isOk = 
           m_impl->thread1.start() 
        && m_impl->thread2.start() 
        && m_impl->calcThread.start();

    if( !isOk )
        return false;

    m_impl->command1 = m_impl->thread1.commandState();
    m_impl->command2 = m_impl->thread2.commandState();
    
    connect( this, SIGNAL( objectDisposed( const qint64 ) ), m_impl->command1, SLOT( disposeObject( const qint64 ) ) );
    connect( this, SIGNAL( objectDisposed( const qint64 ) ), m_impl->command2, SLOT( disposeObject( const qint64 ) ) );

    m_impl->command1->sendCoreCommandMessage( new CoreCommandMessage( CoreCommandMessage::GameStarted ) );
    m_impl->command2->sendCoreCommandMessage( new CoreCommandMessage( CoreCommandMessage::GameStarted ) );

    m_impl->currentView->update();

    return true;
}

//-------------------------------------------------------

bool PolkApp::pauseGame()
{
    if( m_impl->state != ::Running )
        return false;

    m_impl->state = ::Paused;

    m_impl->thread1.pause();
    m_impl->thread2.pause();

    m_impl->calcThread.pause();

    return true;
}

//-------------------------------------------------------

bool PolkApp::stopGame()
{
    /*if( m_impl->State != GameState::Running && m_impl->State != GameState::Paused )
        return false;

    m_impl->State = GameState::Stopped;*/

    return false;
}

//-------------------------------------------------------

void PolkApp::refreshCoordinate( const PtrPObject& obj )
{
    return refreshCoordinate( obj, QPoint() );
}

//-------------------------------------------------------

void PolkApp::refreshCoordinate( const PtrPObject& obj, const QPoint& old )
{
    int x = (int)( qRound( obj->sImpl()->coordinate.x() ) );
    int y = (int)( qRound( obj->sImpl()->coordinate.y() ) );

    if( x == old.x() && y == old.x() )
        return;

    long id = obj->objectID();

    if( !old.isNull() )//delete old position
    {
        m_impl->xCoordinates.remove( old.x(), id );
        m_impl->yCoordinates.remove( old.y(), id );
    }

    m_impl->xCoordinates.insert( x, id );
    m_impl->yCoordinates.insert( y, id );
}
//-------------------------------------------------------
/**
    Регистрирует контроллер комманды. 
    libraryID - id библиотеки, откуда загружать контроллер
    side - сторона, за которую учавствет контроллер

    !!Notice!!
    В случае, если контроллер комманды уже определен, новый НЕ НАЗНАЧАЕТСЯ.
*/
bool PolkApp::registerCommandController( const int libraryID, const int side )
{
    GET_STATE( side );

    return st->registerCommandController( libraryID );
}

//-------------------------------------------------------
/**
    Регистрирует контроллер группы. 
    libraryID - id библиотеки, откуда загружать контроллер
    side - сторона, за которую учавствет контроллер

    ToDo: добавить проверку библиотеки!
*/
int PolkApp::registerGroupController( const int libraryID, const int side )
{
    GET_STATE( side );

    return st->registerGroupController( libraryID );
}

//-------------------------------------------------------
/**
    Регистрирует контроллер объекта. 
    libraryID - id библиотеки, откуда загружать контроллер
    gID - ID группового контроллера
    pObject - объект, которым будет управлять контроллер

    ToDo: добавить проверку библиотеки!
*/
int PolkApp::registerObjectController( const int libraryID, const int side, const int gID, const int pObject )
{
    GET_STATE( side );

    return st->registerObjectController( libraryID, gID, pObject );
}

//-------------------------------------------------------

bool PolkApp::invokeScript( const QString& fileName )
{
    QFile file( fileName );

    if( !file.open( QIODevice::ReadOnly ) )
        return false;

    QDomDocument document;
       
    if( !document.setContent( &file ) )
        return false;

    QDomNodeList intellect = document.elementsByTagName( "Intellect" );

    if( intellect.count() == 0 )
        return true;

    QDomElement intellectElement = intellect.at( 0 ).toElement();

    QDomNodeList maps = intellectElement.elementsByTagName( "Map" );

    for( int i = 0; i < maps.count(); i++ )
    {
        QDomElement map = maps.at( i ).toElement();

        QString fileName = map.attribute( "FileName" );

        if( !reloadMap( fileName ) )
            return false;
    }

    QMap< int, int > libraryMap;

    QDomNodeList dlls = intellectElement.elementsByTagName( "DynamicLibrary" );

    for( int i = 0; i < dlls.count(); i++ )
    {
        QDomElement dll = dlls.at( i ).toElement();

        QString fileName = dll.attribute( "FileName" );
        QString idString = dll.attribute( "ID" );

        int id = idString.toInt();

        int newId = libLoader.loadLibrary( fileName );
        if( newId == 0 )
            return false;

        libraryMap.insert( id, newId );
    }

    QDomNodeList cCtrls = intellectElement.elementsByTagName( "CommandController" );

    for( int i = 0; i < cCtrls.count(); i++ )
    {
        QDomElement cCtrl = cCtrls.at( i ).toElement();

        QString sideString = cCtrl.attribute( "Side" );
        QString idString   = cCtrl.attribute( "LibraryID" );

        int id   = idString.toInt();
        int side = sideString.toInt();

        int newId = registerCommandController( libraryMap[ id ], side );
        if( newId == 0 )
            return false;
    }

    QDomNodeList gCtrls = intellectElement.elementsByTagName( "GroupController" );

    QMap< int, int > groups;
    for( int i = 0; i < gCtrls.count(); i++ )
    {
        QDomElement gCtrl = gCtrls.at( i ).toElement();

        QString sideString = gCtrl.attribute( "Side" );
        QString libString  = gCtrl.attribute( "LibraryID" );
        QString idString   = gCtrl.attribute( "ID" );

        int id   = idString.toInt();
        int lib  = libString.toInt();
        int side = sideString.toInt();

        int newId = registerGroupController( libraryMap[ lib ], side );
        if( newId == 0 )
            return false;
        groups.insert( id, newId );
    }

    QDomNodeList oCtrls = intellectElement.elementsByTagName( "ObjectController" );

    for( int i = 0; i < oCtrls.count(); i++ )
    {
        QDomElement oCtrl = oCtrls.at( i ).toElement();

        QString sideString  = oCtrl.attribute( "Side" );
        QString libString   = oCtrl.attribute( "LibraryID" );
        QString groupString = oCtrl.attribute( "GroupID" );
        QString pObjString  = oCtrl.attribute( "PObjectID" );

        int lib   = libString.toInt();
        int group = groupString.toInt();
        int side  = sideString.toInt();
        int pObj  = pObjString.toInt();

        int newId = registerObjectController( libraryMap[ lib ], side, groups[ group ], pObj );

        if( newId == 0 )
            return false;
    }

    return true;
}

//-------------------------------------------------------

int PolkApp::commandController( const int side )
{
    GET_STATE( side );

    return st->commandController();
}

//-------------------------------------------------------

IDEnumeration PolkApp::groupControllers( const int side )
{
    GET_STATE( side );

    return st->groupControllers();
}
//-------------------------------------------------------
/**
    Выводит список объектов для контроллера группы
    side - играющая сторона, для которой выводится список объектов
    groupID - id группы, у которой прикреплены объекты
*/
IDEnumeration PolkApp::objectControllers( const int side, const int groupID )
{
    GET_STATE( side );

    return st->objectControllers( groupID );
}

//-------------------------------------------------------

int PolkApp::commandControllerLibId( const int side )
{
    GET_STATE( side );

    return st->commandControllerLibId();
}

//-------------------------------------------------------

int PolkApp::groupControllerLibId( const int side, const int groupID )
{
    GET_STATE( side );

    return st->groupControllerLibId( groupID );
}

//-------------------------------------------------------

int PolkApp::objectControllerLibId( const int side, const int objectID )
{
    GET_STATE( side );

    return st->objectControllerLibId( objectID );
}

//-------------------------------------------------------

int PolkApp::objectControllerPObject( const int side, const int objectID )
{
    GET_STATE( side );

    return st->objectControllerPObject( objectID );
}

//-------------------------------------------------------

bool PolkApp::canComeIn( const PtrPObject& who, const MapObject where )
{
    PObject* object = who.get();

    AbstractRocket* rocket = dynamic_cast< AbstractRocket* >( object );

    if( rocket != 0 )
    {
        if( where == FirsrCommandFlag )
            ;
    }

    if( where == Brick || where == Stone || where == Empty )
        return false;

    if( where == Water && !who->canFly() )
        return false;
    
    return true;
}

//-------------------------------------------------------

bool PolkApp::refreshState()
{
    for( PolkAppImpl::PObjectMap::Iterator objectsIter = m_impl->objectIDs.begin();
        objectsIter !=m_impl->objectIDs.end();
        objectsIter++ )
    {
        PtrPObject objectVal = objectsIter.value();

        int id = objectVal->objectID();

        PObjectSharedImpl* info = objectVal->sImpl();

        QPoint point = info->coordinate;
        QPoint speed = info->speed;

        int x0 = point.x();
        int y0 = point.y();

        if( speed.x() == 0 && speed.y() == 0 )
            continue;

        QPoint rotatedSpeed = rotatePoint( speed, info->rotation );

        int dx0 = rotatedSpeed.x();
        int dy0 = rotatedSpeed.y();

        QSize size = objectVal->boundSize();

        int height = size.height();
        int width = size.width();

        int x1 = x0 + dx0;
        int y1 = y0 + dy0;

        if( dy0 != 0 )
        {
            if( dy0 > 0 )
            {
                MapObject objLeft  = objectAt( x1, y1 + height );
                MapObject objRight = objectAt( x1 + width, y1 + height );
                if( !canComeIn( objectVal, objLeft ) || !canComeIn( objectVal, objRight ) )
                {
                    calculateObject( objectVal, x0, y0, x1, y1 );//cY * SQUARE_SIZE + SQUARE_SIZE - height;
                }
            }
            else
            {
                MapObject objLeft  = objectAt( x1, y1 );
                MapObject objRight = objectAt( x1 + width, y1 );
                if( !canComeIn( objectVal, objLeft ) || !canComeIn( objectVal, objRight ) )
                {
                    calculateObject( objectVal, x0, y0, x1, y1 );//cY * SQUARE_SIZE;
                }
            }
        }
        if( dx0 != 0 )
        {
            if( dx0 > 0 )
            {
                MapObject objTop = objectAt( x1 + width, y1 );
                MapObject objBottom = objectAt( x1 + width, y1 + height );
                if( !canComeIn( objectVal, objTop ) || !canComeIn( objectVal, objBottom ) )
                {
                    calculateObject( objectVal, x0, y0, x1, y1 );//cX * SQUARE_SIZE + SQUARE_SIZE - width;
                }
            }
            else
            {
                MapObject objTop = objectAt( x1, y1 );
                MapObject objBottom = objectAt( x1, y1 + height );
                if( !canComeIn( objectVal, objTop ) || !canComeIn( objectVal, objBottom ) )
                {
                    calculateObject( objectVal, x0, y0, x1, y1 );//cX * SQUARE_SIZE;
                }
            }
        }

        const QRect mySelf( point, size );

        int parentID = objectVal->parentID();

        for( PolkAppImpl::PObjectMap::ConstIterator iter = m_impl->objectIDs.constBegin();
            iter != m_impl->objectIDs.constEnd();
            iter++ )
        {
            PtrPObject anotherObj = iter.value();

            int anotherId = anotherObj->objectID();

            if( anotherId == id || parentID == anotherId )
                continue;

            QPoint p = anotherObj->position();
            QSize  s = anotherObj->boundSize();

            QRect another( p, s );

            PObject::OnCollision onCollision = objectVal->onCollision();

            bool permutate = false;

            if( dy0 > 0 )
            {
                permutate |= another.contains( x1, y1 + width ) || another.contains( x1 + width, y1 + height );
                permutate |= mySelf.contains( another.left(), another.bottom() ) ||mySelf.contains( another.right(), another.bottom() ) ;
            } else if( dy0 < 0 )
            {
                permutate |= another.contains( x1, y1 ) || another.contains( x1 + width, y1 );
                permutate |= mySelf.contains( another.left(), another.top() ) ||mySelf.contains( another.right(), another.top() ) ;
            }

            if( dx0 > 0 )
            {
                permutate |= another.contains( x1 + width, y1 ) || another.contains( x1 + width, y1 + height );
                permutate |= mySelf.contains( another.left(), another.bottom() ) ||mySelf.contains( another.left(), another.top() ) ;
            } else if( dx0 < 0 )
            {
                permutate |= another.contains( x1, y1 ) || another.contains( x1, y1 + height );
                permutate |= mySelf.contains( another.right(), another.bottom() ) ||mySelf.contains( another.right(), another.top() ) ;
            }

            if( permutate )
            {
                if( onCollision & PObject::Revert )
                {
                    x1 = x0;
                    y1 = y0;
                }
                if( onCollision & PObject::DisposeMyself )
                {
                    disposeObject( objectVal );
                }
                if( onCollision & PObject::DisposeAnother )
                {
                    disposeObject( anotherObj );
                }
            }
        }

        info->coordinate.setX( x1 );
        info->coordinate.setY( y1 );
    }

    deleteDisposedObjects();

    emit updateVisualState();

    return true;
}

//-------------------------------------------------------

bool PolkApp::userPressKey( Qt::Key key )
{
    if( !m_impl->keyMap.contains( key ) )
        return false;

    IAbstractInputDriver* iDriver = m_impl->keyMap[ key ];

    iDriver->processKey( key );
    return true;
}


//-------------------------------------------------------

bool PolkApp::registerKey( Qt::Key key, IAbstractInputDriver* driver )
{   
    if( m_impl->keyMap.contains( key ) )
        return false;

    m_impl->keyMap.insert( key, driver );

    return true;
}

//-------------------------------------------------------

bool PolkApp::setSpeed( const PtrPObject& object, const QPoint& persent )
{
    if( persent.x() > 100 || persent.y() > 100 ||  persent.x() < 0 || persent.y() < 0 )
        return false;

    QPoint max = object->maxSpeed();

    object->sImpl()->speed = QPoint( max.x() * persent.x() / 100, max.y() * persent.y() / 100 );

    return true;
}

//-------------------------------------------------------

bool PolkApp::setRotation( const PtrPObject& object, int angle )
{
    if( object.get() == 0 )
        return false;

    object->sImpl()->rotation = angle;
    return true;
}

//-------------------------------------------------------

PtrPObject PolkApp::getNewObject( const int side, const int rtti )
{
    PtrPObject result;

    switch( rtti )
    {
    case SimpleTank::RTTI :
        {
            result = PtrPObject( new SimpleTank( side ) );

            QPoint point = m_impl->map.getRandomTankPlace( side );

            result->sImpl()->coordinate = QPoint( point.x() * SQUARE_SIZE, point.y() * SQUARE_SIZE );            

            break;
        }
    }

    if( result.get() )
        addObjectOnScene( result );

    return result;
}

//-------------------------------------------------------

void PolkApp::disposeObject( const PtrPObject& object )
{
    m_impl->objectsToDelete.append( object );

    return;
}

//-------------------------------------------------------

void PolkApp::makeRocket( const PtrPObject& who )
{
    PObject* obj = who.get();

    IShootableObject* object = dynamic_cast< IShootableObject* >( obj );

    if( object == 0 )
        return;

    int rocketRTTI = object->atackObject();

    AbstractRocket* rocket = 0;

    switch( rocketRTTI )
    {
    case SimpleRocket::RTTI :
        {
            rocket = new SimpleRocket( who->side(), obj->objectID() );
            break;
        }
    default:
        return;
    }

    if( rocket == 0 )
        return;

    PObjectSharedImpl* pImpl = rocket->sImpl();

    pImpl->rotation = who->rotation();
    pImpl->speed = QPoint( rocket->maxSpeed().x(), 0 );
    pImpl->coordinate = object->startPoint();

    PtrPObject rocketObject( rocket ); 

    addObjectOnScene( rocketObject );
}

//-------------------------------------------------------

void PolkApp::deleteDisposedObjects()
{
    QVector< PtrPObject >& objects = m_impl->objectsToDelete;

    for( int i = 0; i < objects.size(); i++ )
    {
        PtrPObject obj = objects[ i ];

        qint64 id = obj->objectID();

        m_impl->objectIDs.remove( id );
    
        m_impl->removedObjects[ id ] = obj;

        emit objectDeleted( id );

        GET_STATE( obj->side() );

        st->disposeObject( id );

        emit objectDisposed( id );
    }

    objects.clear();
}
 
//-------------------------------------------------------

