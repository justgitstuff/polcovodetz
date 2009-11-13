#ifndef  __POLK_APP__
#define  __POLK_APP__

//-------------------------------------------------------

#include <Core/PObjects/PObject.h>

#include <boost/shared_ptr.hpp>

#include <QObject>
#include <QVector>


//-------------------------------------------------------

struct  PolkAppImpl;

class  GlobalPoint;
class  Map;
class  QPoint;
class  QWidget;
class  GUIControler;
class  PrtPObject;
class  WinState;

enum   MapObject;

struct DriversStorage;
class  IAbstractInputDriver;
class  ICommandController;

//-------------------------------------------------------

typedef QVector< qint64 > IDEnumeration;

//-------------------------------------------------------
/** Главный управляющий класс проекта.
    Так называемое "Ядро"
*/
class PolkApp : public QObject
{
    Q_OBJECT;
public:
static const int               SQUARE_SIZE = 2 << 14;

                               PolkApp();
                               ~PolkApp();

           QWidget*            currentView()const;

           const Map&          map()const;
            
           bool                addObjectOnScene( const PtrPObject& );

           bool                reloadMap( const QString& fileName );

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

           bool                registerKey( Qt::Key key, IAbstractInputDriver* driver );

           bool                setSpeed( const PtrPObject&, const QPoint& persent );
           bool                setRotation( const PtrPObject&, int angle );

           bool                canComeNext( const PtrPObject& obj, const QPoint& speed )const;

           /**
            Выдает новый объект на карте с заданным rtti 
           */
           PtrPObject          getNewObject( const int side, const int rtti );
           void                makeRocket( const PtrPObject& who );

           /**
            Выводит объект из системы.
           */
           void                disposeObject( const PtrPObject& object );

           /**
            Может ли объект войти в клетку
           */
              bool             checkComeIn( const PtrPObject& who, const MapObject& where );

           /**
            Может ли объект войти в клетку
           */
       static bool             canComeIn( const PtrPObject& who, const MapObject& where );

           /**
            Может ли нелетающий объект войти в клетку
           */
       static bool             canComeIn( const MapObject& where );

           /**
            Может ли летающий объект войти в клетку
           */
       static bool             canFlyIn( const MapObject& where );

signals:
           void                showCrash( const QPoint& where );
           void                updateVisualState();
           void                objectDeleted( const qint64 id );
           void                objectAdded( const PtrPObject& );

           void                objectDisposed( const qint64 );

           void                gameOver( const WinState& );

public slots:
           bool          startGame();
           bool          pauseGame();
           bool          stopGame();

           bool          refreshState();

           bool          userPressKey( Qt::Key key );

private:
           boost::shared_ptr< PolkAppImpl > m_impl;   

           void          refreshCoordinate( const PtrPObject& obj, const QPoint& old ); 
           void          refreshCoordinate( const PtrPObject& obj );

inline     void          deleteDisposedObjects();

};

//-------------------------------------------------------

extern PolkApp pApp;

//-------------------------------------------------------

#endif //__POLK_APP__