#ifndef  __POLK_APP__
#define  __POLK_APP__

//-------------------------------------------------------

#include <Core/PObjects/PObject.h>
#include <boost/shared_ptr.hpp>

#include <QVector>

//-------------------------------------------------------

struct  PolkAppImpl;

class  Map;
class  QPoint;
class  QWidget;
class  GUIControler;

struct DriversStorage;
class  ICommandController;

//-------------------------------------------------------

typedef QVector< int > IDEnumeration;

//-------------------------------------------------------
/** Главный управляющий класс проекта.
    Так называемое "Ядро"
*/
class PolkApp : public QObject
{
    Q_OBJECT;
public:
                        PolkApp();
                        ~PolkApp();

    QWidget*            currentView()const;

    const Map&          map()const;
    
    bool                addObjectOnScene( const int side, const PtrPObject& );

    //bool          addObject();

    bool                reloadMap( const QString& fileName );

    bool                invokeScript( const QString& fileName );

    bool                registerCommandController( const int libraryID, const int side );
    int                 registerGroupController( const int libraryID, const int side );
    int                 registerObjectController( const int libraryID, const int side, const int gID, const int pObject );

    int                 commandController( const int side );
    IDEnumeration       groupControllers( const int side );
    IDEnumeration       objectControllers( const int side, const int groupID );

    int                 commandControllerLibId( const int side );
    int                 groupControllerLibId( const int side, const int groupID );
    int                 objectControllerLibId( const int side, const int objectID );
    int                 objectControllerPObject( const int side, const int objectID );

public slots:
    bool          startGame();
    bool          pauseGame();
    bool          stopGame();

private:
    boost::shared_ptr< PolkAppImpl > m_impl;   

    void          refreshCoordinate( const PtrPObject& obj, const QPoint& old ); 
    void          refreshCoordinate( const PtrPObject& obj ); 
};

//-------------------------------------------------------

extern PolkApp pApp;

//-------------------------------------------------------

#endif //__POLK_APP__