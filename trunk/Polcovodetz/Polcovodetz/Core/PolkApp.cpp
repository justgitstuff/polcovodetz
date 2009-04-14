
//-------------------------------------------------------

#include <Core/PolkApp.h>

#include <Core/BaseClasses/ICommandController.h>
#include <Core/BaseClasses/IGroupController.h>
#include <Core/BaseClasses/IObjectController.h>
#include <Core/BaseClasses/ILoader.h>
#include <Core/Common/Map.h>
#include <Core/Drivers/SimpleCommandDrivers.h>
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

typedef ILoader* (*LoadFunction)();

//-------------------------------------------------------

struct DriversStorage
{
    ICommandInputDriver*  ciDriver;
    ICommandOutputDriver* coDriver;

    ICommandController*   cController;
};

//-------------------------------------------------------

struct PolkAppImpl
{
    typedef QMap< long, PtrPObject >                  PObjectMap;
    typedef QMap< long, int >                         PObjectSideMap;
 
    typedef QMultiMap< int, long >                    PObjectCoordinateMap;//coordinate to list of ids

    typedef QMap< int, boost::shared_ptr< ILoader > > LibraryMap;
    typedef QMap< int, LibDefinition >                LibraryInfoMap;

    typedef QVector< IAbstractController* >           Controllers;

    DriversStorage        drivers1;
    DriversStorage        drivers2;

    LibraryMap            libraryMap;
    LibraryInfoMap        libraryInfoMap;

    Controllers           loadedControllers;

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

PolkApp::~PolkApp()
{
    for( int i = 0; i < m_impl->loadedControllers.count(); i++ )
    {
        delete m_impl->loadedControllers[ i ];
    }
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
/**
«агружает библиотеку, определ€ет доступные в ней классы и отправл€ет сигнал, в случае успешной загрузки.

¬озвращает привоенный id.
*/
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

    LoadFunction lf = ( LoadFunction )f;

    try
    {
        ILoader* lib = lf();

        m_impl->loadInfoView->append( tr( "Loader " ) + lib->name() + tr( " WasLoaded" ) );

        boost::shared_ptr< ILoader > newLib( lib );

        static int SHARED_LIB_ID = 1;

        int id = SHARED_LIB_ID++;

        m_impl->libraryMap.insert( id, newLib );

        LibDefinition libDef;

        libDef.id          = id;
        libDef.name        = newLib->name();
        libDef.descritpion = newLib->description();

        boost::shared_ptr< ICommandController > cc( lib->getCommandController() );
        boost::shared_ptr< IGroupController >   gc( lib->getGroupController() );
        boost::shared_ptr< IObjectController >  oc( lib->getObjectController() );

        if( cc.get() != 0 )
        {
            libDef.ccName        = cc->name();
            libDef.ccDescription = cc->description();
        }
        if( gc.get() != 0 )
        {
            libDef.gcName        = gc->name();
            libDef.gcDescription = gc->description();
        }
        if( oc.get() != 0 )
        {
            libDef.ocName        = oc->name();
            libDef.ocDescription = oc->description();
        }

        m_impl->libraryInfoMap.insert( id, libDef );

        emit newLibrary( libDef );

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

ICommandController* PolkApp::loadCommandController( const int libraryID )
{
    if( !m_impl->libraryMap.contains( libraryID ) )
        return 0;

    ILoader* loader = m_impl->libraryMap[ libraryID ].get();

    ICommandController* cc = loader->getCommandController();

    if( cc == 0 )
        return 0;

    m_impl->loadedControllers.append( cc );

    return cc;
}

//-------------------------------------------------------

PolkApp::LibDefinitions PolkApp::loadedLibraries()const
{
    return m_impl->libraryInfoMap.values();
}

//-------------------------------------------------------

bool PolkApp::registerCommandController( const int libraryID, const int side )
{
    createCommandDrivers( side );

    DriversStorage& ds = side == 1 ? m_impl->drivers1 : m_impl->drivers2;

    if( ds.cController != 0 )
        return false;

    return false;
}

//-------------------------------------------------------
void PolkApp::createCommandDrivers( const int side )
{
    DriversStorage& ds = side == 1 ? m_impl->drivers1 : m_impl->drivers2;

    if( ds.ciDriver == 0 )
        ds.ciDriver = new SimpleCommandInputDriver();

    if( ds.coDriver == 0 )
        ds.coDriver = new SimpleCommandOutputDriver();
}

//-------------------------------------------------------
