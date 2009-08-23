
#ifndef  __COMMAND_THREAD__
#define  __COMMAND_THREAD__

//-------------------------------------------------------

#include <Core/PObjects/PObject.h>

#include <QThread>

#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct CommandThreadImpl;
class CoreCommandMessage;

//-------------------------------------------------------

typedef QVector< int > IDEnumeration;

//-------------------------------------------------------

class CommandThread : public QThread
{
    Q_OBJECT;
public:
    CommandThread( const int side );

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


    bool start(); //asynchronus
    bool pause(); //asynchronus
    bool stop();  //asynchronus

protected:
    void run();

private:
    boost::shared_ptr< CommandThreadImpl > m_impl;

    bool connectDrivers();
    bool initDrivers();
    void sendInnerMessages( const int maxMessages = 100 );
};

//-------------------------------------------------------

#endif //__COMMAND_THREAD__