
//-------------------------------------------------------

#include <Core/PolkApp.h>

#include <Core/BaseClasses/Messages.h>
#include <Core/Common/Map.h>
#include <Core/LibraryLoader.h>
#include <Core/MultiThreading/CalcThread.h>
#include <Core/MultiThreading/CommandThread.h>
#include <Core/PObjects/PObject.h>
#include <Core/PObjects/PObjectSharedImpl.h>
#include <GUI/SpecialControls/PaintArea2D.h>

#include <QtDebug>
#include <QDomDocument>
#include <QFile>
#include <QMap>
#include <QMultiMap>
#include <QPluginLoader>
#include <QPoint>
#include <QSize>
#include <QTextEdit>

//-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!

#include <Core/PObjects/UserObjects/Moving/SimpleTank.h>

//-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!

#define GET_THREAD(side) CommandThread& ct = side == 1 ? m_impl->command1 : m_impl->command2;

//-------------------------------------------------------

//typedef MapObject MapObject;

//-------------------------------------------------------

PolkApp pApp;

//-------------------------------------------------------

struct PolkAppImpl
{    
    PolkAppImpl():command1(), command2(), calcThread(){};
    typedef QMap< long, PtrPObject >  PObjectMap;
    typedef QMap< long, int >         PObjectSideMap;
 
    typedef QMultiMap< int, long >    PObjectCoordinateMap;//coordinate to list of ids

    Map                   map;

    PObjectMap            objectIDs;
    PObjectSideMap        objectSides;

    PObjectCoordinateMap  xCoordinates;       
    PObjectCoordinateMap  yCoordinates;

    GUIControler*         currentView;

    CalcThread            calcThread;

    CommandThread         command1;
    CommandThread         command2;
};

//-------------------------------------------------------

PolkApp::PolkApp()
{
    m_impl.reset( new PolkAppImpl() );

    m_impl->currentView  = 0;
}

//-------------------------------------------------------

PolkApp::~PolkApp()
{}

//-------------------------------------------------------

bool PolkApp::addObjectOnScene( const int side, const PtrPObject& obj )
{
    qint64 id = obj->objectID();

    m_impl->objectSides.insert( id, side );
    m_impl->objectIDs.insert( id, obj );

    m_impl->currentView->addObject( obj );

    obj->sImpl()->coordinate = QPoint( 0, 0 );

    refreshCoordinate( obj );

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
        m_impl->currentView = new GUIControler();

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
    bool isOk = /*m_impl->visualThread.start() 
        &&*/ m_impl->command1.start() 
        && m_impl->command2.start();

    if( !isOk )
        return false;

    /* подкрепление ВСЕХ драйверов КРОМЕ драйвера от объекта к PObject`у*/
    /* посылка сообщений о пустых местах к СС */
   // addObjectOnScene( 1, PtrPObject( new SimpleTank( 1 ) ) );
    
    m_impl->command1.sendCoreCommandMessage( new CoreCommandMessage( CoreCommandMessage::GameStarted ) );
    m_impl->command2.sendCoreCommandMessage( new CoreCommandMessage( CoreCommandMessage::GameStarted ) );

    return true;
}

//-------------------------------------------------------

bool PolkApp::pauseGame()
{
    return false;
}

//-------------------------------------------------------

bool PolkApp::stopGame()
{
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
    GET_THREAD( side );

    return ct.registerCommandController( libraryID );
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
    GET_THREAD( side );

    return ct.registerGroupController( libraryID );
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
    GET_THREAD( side );

    return ct.registerObjectController( libraryID, gID, pObject );
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
    GET_THREAD( side );

    return ct.commandController();
}

//-------------------------------------------------------

IDEnumeration PolkApp::groupControllers( const int side )
{
    GET_THREAD( side );

    return ct.groupControllers();
}
//-------------------------------------------------------
/**
    Выводит список объектов для контроллера группы
    side - играющая сторона, для которой выводится список объектов
    groupID - id группы, у которой прикреплены объекты
*/
IDEnumeration PolkApp::objectControllers( const int side, const int groupID )
{
    GET_THREAD( side );

    return ct.objectControllers( groupID );
}

//-------------------------------------------------------

int PolkApp::commandControllerLibId( const int side )
{
    GET_THREAD( side );

    return ct.commandControllerLibId();
}

//-------------------------------------------------------

int PolkApp::groupControllerLibId( const int side, const int groupID )
{
    GET_THREAD( side );

    return ct.groupControllerLibId( groupID );
}

//-------------------------------------------------------

int PolkApp::objectControllerLibId( const int side, const int objectID )
{
    GET_THREAD( side );

    return ct.objectControllerLibId( objectID );
}

//-------------------------------------------------------

int PolkApp::objectControllerPObject( const int side, const int objectID )
{
    GET_THREAD( side );

    return ct.objectControllerPObject( objectID );
}

//-------------------------------------------------------

bool PolkApp::canComeIn( const PtrPObject& who, const MapObject where )
{
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

        PObjectSharedImpl* info = objectVal->sImpl();

        int x0 = info->coordinate.x();
        int y0 = info->coordinate.y();

        int dx0 = info->speed.x();
        int dy0 = info->speed.y();

        if( dx0 == 0 && dy0 == 0 )
            continue;

        int x1 = x0 + dx0;
        int y1 = y0 + dy0;
        
        int cX = x0 % 32;
        int cY = y0 % 32;

        int sx1 = cX * 32 - 32;
        int sx2 = sx1 + 32;
        int sx3 = sx2 + 32;
//        int sx4 = sx3 + 32;

        int sy1 = cY * 32 - 32;
        int sy2 = sy1 + 32;
        int sy3 = sy2 + 32;
//        int sy4 = sy3 + 32;        

        if( dy0 != 0 )
        {
            if( dy0 > 0 )
            {
                MapObject obj = m_impl->map.objectAt( cX, cY + 1 );
                if( !canComeIn( objectVal, obj ) )
                {
                    if( y1 < sy2 )
                        y1 = sy2;
                }
            }
            else
            {
                MapObject obj = m_impl->map.objectAt( cX, cY - 1 );
                if( !canComeIn( objectVal, obj )  )
                {
                    if( y1 > sy3 )
                        y1 = sy3;
                }
            }
        }
        if( dx0 != 0 )
        {
            if( dx0 > 0 )
            {
                MapObject obj = m_impl->map.objectAt( cX + 1, cY );
                if( !canComeIn( objectVal, obj ) )
                {
                    if( x1 < sx2 )
                        x1 = sx2;
                }
            }
            else
            {
                MapObject obj = m_impl->map.objectAt( cX + 1, cY );
                if( !canComeIn( objectVal, obj ) )
                {
                    if( x1 > sx3 )
                        x1 = sx3;
                }
            }

            info->coordinate.setX( x1 );
            info->coordinate.setY( y1 );
        }

        if( dx0 == 0 || dy0 == 0 )
        {
            info->coordinate.setX( x1 );
            info->coordinate.setY( y1 );

            continue;        
        }

        if( x1 > sx3 && y1 > sy3 )
        {
            if( !canComeIn( objectVal, m_impl->map.objectAt( cX + 1, cY + 1 ) ) )
            {
                y1 = y1 > sy3 ? sy3 : y1;
                x1 = x1 > sx3 ? sx3 : x1;
            }
        }

        if( x1 < sx2 && y1 > sy3 )
        {
            if( !canComeIn( objectVal, m_impl->map.objectAt( cX - 1, cY + 1 ) ) )
            {
                y1 = y1 > sy3 ? sy3 : y1;
                x1 = x1 < sx2 ? sx2 : x1;
            }
        }

        if( x1 > sx3 && y1 < sy2 )
        {
            if( !canComeIn( objectVal, m_impl->map.objectAt( cX + 1, cY - 1 ) ) )
            {
                y1 = y1 < sy2 ? sy2 : y1;
                x1 = x1 > sx3 ? sx3 : x1;
            }
        }

        if( x1 < sx2 && y1 < sy2 )
        {
            if( !canComeIn( objectVal, m_impl->map.objectAt( cX - 1, cY - 1 ) ) )
            {
                y1 = y1 < sy2 ? sy2 : y1;
                x1 = x1 < sx2 ? sx2 : x1;
            }
        }

        info->coordinate.setX( x1 );
        info->coordinate.setY( y1 );
   }

    return false;
}

//-------------------------------------------------------

inline bool isLeft( const int x1,  const int x2,  const int x3, const int y1,  const int y2,  const int y3 )
{
    int res = 
        x1 * y2 - x2 * y1 +
        x2 * y3 - x3 * x2 + 
        x3 * y1 - x1 * y3;

    return res > 0;
}

//-------------------------------------------------------

inline bool isLeft( const QPoint& p1, const QPoint& p2, const QPoint& p3 )
{
    int x1 = p1.x();
    int x2 = p2.x();
    int x3 = p3.x();
    int y1 = p1.y();
    int y2 = p2.y();
    int y3 = p3.y();

    return isLeft( x1, x2, x3, y1, y2, y3 );
}

//-------------------------------------------------------

inline bool permutateRectangle( const QPoint& pos1, const QPoint& pos2, const QRect& rect )
{
    int x1 = pos1.x();
    int x2 = pos2.x();

    int y1 = pos1.y();
    int y2 = pos2.y();

    int rx1 = rect.x();
    int rx2 = rect.x() + rect.width();

    int ry1 = rect.y();
    int ry2 = rect.y() + rect.height();

    if( x1 < rx1 && x2 < rx1 )
        return false;

    if( x1 > rx2 && x2 > rx2 )
        return false;

    if( y1 < ry1 && y2 < ry1 )
        return false;

    if( y1 > ry2 && y2 > ry2 )
        return false;

    bool p1 = isLeft( x1, x2, rx1, y1, y2, ry1 );
    bool p2 = isLeft( x1, x2, rx2, y1, y2, ry1 );
    bool p3 = isLeft( x1, x2, rx1, y1, y2, ry2 );
    bool p4 = isLeft( x1, x2, rx2, y1, y2, ry2 );

    return ( p1 & p2 & p3 & p4 ) | ( (!p1) & (!p2) & (!p3) & (!p4) );//все слева или все справа
}

//-------------------------------------------------------

inline bool permutateRectangle( const QPoint& pos1, const QPoint& pos2, const QSize& size, const QRect& rect )
{
    QRect rect2 = rect;
    rect2.setX( rect.x() - size.width() );
    rect2.setY( rect.y() - size.height() );
    rect2.setWidth( rect.width() + size.width() * 2 );
    rect2.setHeight( rect.height() + size.height() * 2 );

    return permutateRectangle( pos1, pos2, rect );
}

//-------------------------------------------------------

