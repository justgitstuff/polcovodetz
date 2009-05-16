#ifndef  __POLK_APP__
#define  __POLK_APP__

//-------------------------------------------------------

#include <Core/PObjects/PObject.h>
#include <boost/shared_ptr.hpp>

#include <QList>

//-------------------------------------------------------

struct PolkAppImpl;

class Map;
class QPoint;
class QWidget;
class GUIControler;

class ICommandController;

//-------------------------------------------------------
/**
    Хранит инфорацию о подгружаемой библиотеке.
*/
struct LibDefinition
{
    int     id;

    QString name;
    QString descritpion;

    QString ccName;
    QString ccDescription;
    QString gcName;
    QString gcDescription;
    QString ocName;
    QString ocDescription;
};

//-------------------------------------------------------
/** Главный управляющий класс проекта.
    Так называемое "Ядро"
*/
class PolkApp : public QObject
{
    Q_OBJECT;
public:

    typedef const QList<LibDefinition> LibDefinitions;

                        PolkApp();
                        ~PolkApp();

    QWidget*            currentView()const;
    QWidget*            loadInfoView()const;

    const Map&          map()const;
    
    bool                addObjectOnScene( const int side, const PtrPObject& );

    //bool          addObject();

    bool                reloadMap( const QString& fileName );

    int                 loadLibrary( const QString& fileName );

    ICommandController* loadCommandController( const int libraryID );

    bool                registerCommandController( const int libraryID, const int side );
    int                 registerGroupController( const int libraryID, const int side );
    int                 registerObjectController( const int libraryID, const int side, const int gID, const int pObject );

    LibDefinitions      loadedLibraries()const;
    LibDefinition       library( const int id );

signals:
    void          newLibrary( const LibDefinition& );

public slots:
    bool          startGame();
    bool          pauseGame();
    bool          stopGame();

private:
    boost::shared_ptr< PolkAppImpl > m_impl;   

    void          refreshCoordinate( const PtrPObject& obj, const QPoint& old ); 
    void          refreshCoordinate( const PtrPObject& obj ); 

    void          createCommandDrivers( const int side );
};

//-------------------------------------------------------

extern PolkApp pApp;

//-------------------------------------------------------

#endif //__POLK_APP__