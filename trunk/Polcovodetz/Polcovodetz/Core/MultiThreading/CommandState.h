
#ifndef  __COMMAND_STATE__
#define  __COMMAND_STATE__

//-------------------------------------------------------

#include <QObject>

#include <boost/shared_ptr.hpp>

#include <Core/PObjects/PObject.h>

//-------------------------------------------------------

struct CommandStateImpl;
class CoreCommandMessage;
class AbstractMessage;
class DriverHelper;

//-------------------------------------------------------

typedef QVector< int > IDEnumeration;

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

class CommandState : public QObject
{
    Q_OBJECT;
public:
    
    CommandState( const int side );

    int                 side()const;

    bool                registerCommandController( const int libraryID );
    int                 registerGroupController( const int libraryID );
    int                 registerObjectController( const int libraryID, const int gID, const int pObject );

    int                 commandController();
    IDEnumeration       groupControllers();
    IDEnumeration       objectControllers( const int groupID );

    int                 commandControllerLibId();
    int                 groupControllerLibId( const int groupID );
    int                 objectControllerLibId( const int objectID );
    int                 objectControllerPObject( const int objectID );

    int                 sendCoreCommandMessage( CoreCommandMessage* message );

    bool                setSpeed( const PtrPObject&, const QPoint& persent );
    bool                setRotation( const PtrPObject&, int angle );
     
    void                createConnectedObject( const int rtti, const qint64 driverID );

    void                makeRocket( const PtrPObject& who );

    bool                connectDrivers();
    void                sendInnerMessages( const int maxMessages = 100 );

    DriverHelper*       driverHelper()const;

public slots:
    void                disposeObject( const qint64 id );

private:

    boost::shared_ptr< CommandStateImpl > m_impl;
};

//-------------------------------------------------------

#endif //__COMMAND_STATE__