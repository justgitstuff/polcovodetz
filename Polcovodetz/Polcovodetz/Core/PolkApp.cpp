
//-------------------------------------------------------

#include <Core/PolkApp.h>

#include <Core/BaseClasses/ICommandController.h>
#include <Core/BaseClasses/ILoader.h>
#include <Core/Common/Map.h>
#include <Core/MultiThreading/CommandThread.h>
#include <Core/MultiThreading/VisualThread.h>
#include <Core/PObjects/PObject.h>
#include <Core/PObjects/PObjectSharedImpl.h>
#include <GUI/SpecialControls/PaintArea2D.h>

#include <QtDebug>
#include <QFile>
#include <QMap>
#include <QMultiMap>
#include <QPluginLoader>
#include <QPoint>
#include <QTextEdit>

//-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!

#include <Core/PObjects/UserObjects/Moving/SimpleTank.h>

//-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!


//-------------------------------------------------------

PolkApp pApp;

//-------------------------------------------------------

typedef ILoader* (*CCFunction)();

//-------------------------------------------------------

struct PolkAppImpl
{
    typedef QMap< long, PtrPObject >                  PObjectMap;
    typedef QMap< long, int >                         PObjectSideMap;
 
    typedef QMultiMap< int, long >                    PObjectCoordinateMap;//coordinate to list of ids

    typedef QMap< int, boost::shared_ptr< ILoader > > LibraryMap;

    LibraryMap            libraryMap;

    Map                   map;

    PObjectMap            objectIDs;
    PObjectSideMap        objectSides;

    PObjectCoordinateMap  xCoordinates;       
    PObjectCoordinateMap  yCoordinates;

    GUIControler*         currentView;
    QTextEdit*            loadInfoView;

    VisualThread          visualThread;
    CommandThread         command1Thread;
    CommandThread         command2Thread;
};

//-------------------------------------------------------

PolkApp::PolkApp()
{
    m_impl.reset( new PolkAppImpl() );

    m_impl->currentView  = 0;
    m_impl->loadInfoView = 0;
}

//-------------------------------------------------------

bool PolkApp::addObjectOnScene( const int side, const PtrPObject& obj )
{
    qint64 id = obj->objectID();

    m_impl->objectSides.insert( id, side );
    m_impl->objectIDs.insert( id, obj );

    m_impl->currentView->addObject( obj );

    obj->sImpl()->coordinate = QPointF( 0, 0 );

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
    bool isOk = m_impl->visualThread.start() 
        && m_impl->command1Thread.start() 
        && m_impl->command2Thread.start();

    addObjectOnScene( 1, PtrPObject( new SimpleTank( 1 ) ) );

    return false;
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

int PolkApp::loadLibrary( const QString& fileName )
{
    QLibrary lib( fileName );

    if( m_impl->loadInfoView == 0 )
    {
        m_impl->loadInfoView = new QTextEdit();

        m_impl->loadInfoView->setReadOnly( true );
    }

    if( !lib.load() )
    {
        m_impl->loadInfoView->append( tr( "Can`tLoadLibrary: " ) + lib.errorString() );

        return 0;
    }

    void* f = lib.resolve( "getLoader" );

    if( f == 0 )
    {
        m_impl->loadInfoView->append( tr( "Can`tLoadLoader: " ) + lib.errorString() );

        return 0;
    }

    CCFunction cc = ( CCFunction )f;

    try
    {
        ILoader* lib = cc();

        m_impl->loadInfoView->append( tr( "Loader " ) + lib->name() + tr( " WasLoaded" ) );

        boost::shared_ptr< ILoader > newLib( lib );

        static int SHARED_LIB_ID = 1;

        int id = SHARED_LIB_ID++;

        m_impl->libraryMap.insert( id, newLib );

        return id;
    }
    catch( ... )
    {
        m_impl->loadInfoView->append( tr( "UnknownErrorDuringLoadLoader: " ) );

        return 0;
    }

}

//-------------------------------------------------------

QWidget* PolkApp::loadInfoView()const
{
    if( m_impl->loadInfoView == 0 )
    {
        m_impl->loadInfoView = new QTextEdit();

        m_impl->loadInfoView->setReadOnly( true );
    }

    return m_impl->loadInfoView;
}

//-------------------------------------------------------

