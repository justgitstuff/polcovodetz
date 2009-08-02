
//-------------------------------------------------------

#include <Core/LibraryLoader.h>

#include <Core/BaseClasses/ICommandController.h>
#include <Core/BaseClasses/IGroupController.h>
#include <Core/BaseClasses/IObjectController.h>
#include <Core/BaseClasses/ILoader.h>
#include <Core/PolkApp.h>

#include <QLibrary>
#include <QMap>
#include <QTextEdit>

//-------------------------------------------------------

LibraryLoader libLoader;

//-------------------------------------------------------

typedef ILoader* (*LoadFunction)();

//-------------------------------------------------------

struct LibraryLoaderImpl
{
    typedef QMap< int, boost::shared_ptr< ILoader > > LibraryMap;
    typedef QMap< int, LibDefinition >                LibraryInfoMap;

    typedef QVector< IAbstractController* >           Controllers;

    LibraryMap            libraryMap;
    LibraryInfoMap        libraryInfoMap;

    QTextEdit*            loadInfoView;

    Controllers           loadedControllers;
};

//-------------------------------------------------------

LibraryLoader::LibraryLoader()
{
    m_impl.reset( new LibraryLoaderImpl() );

    m_impl->loadInfoView = 0;
}

//-------------------------------------------------------

LibraryLoader::~LibraryLoader()
{
}

//-------------------------------------------------------


//-------------------------------------------------------
/**
«агружает библиотеку, определ€ет доступные в ней классы и отправл€ет сигнал, в случае успешной загрузки.

¬озвращает привоенный id.
*/
int LibraryLoader::loadLibrary( const QString& fileName )
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

LibDefinition LibraryLoader::library( const int id )const
{
    return m_impl->libraryInfoMap[ id ];
}

//-------------------------------------------------------

QWidget* LibraryLoader::loadInfoView()const
{
    if( m_impl->loadInfoView == 0 )
    {
        m_impl->loadInfoView = new QTextEdit();

        m_impl->loadInfoView->setReadOnly( true );
    }

    return m_impl->loadInfoView;
}

//-------------------------------------------------------

ICommandController* LibraryLoader::loadCommandController( const int libraryID )
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

IGroupController* LibraryLoader::loadGroupController( const int libraryID )
{
    if( !m_impl->libraryMap.contains( libraryID ) )
        return 0;

    ILoader* loader = m_impl->libraryMap[ libraryID ].get();

    IGroupController* cc = loader->getGroupController();

    if( cc == 0 )
        return 0;

    m_impl->loadedControllers.append( cc );

    return cc;
}

//-------------------------------------------------------

IObjectController* LibraryLoader::loadObjectController( const int libraryID )
{
    if( !m_impl->libraryMap.contains( libraryID ) )
        return 0;

    ILoader* loader = m_impl->libraryMap[ libraryID ].get();

    IObjectController* cc = loader->getObjectController();

    if( cc == 0 )
        return 0;

    m_impl->loadedControllers.append( cc );

    return cc;
}

//-------------------------------------------------------

LibraryLoader::LibDefinitions LibraryLoader::loadedLibraries()const
{
    return m_impl->libraryInfoMap.values();
}

