
#ifndef  __COMMAND_THREAD__
#define  __COMMAND_THREAD__

//-------------------------------------------------------

#include <QThread>

#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct CommandThreadImpl;
class CommandState;

//-------------------------------------------------------

typedef QVector< int > IDEnumeration;

//-------------------------------------------------------

class CommandThread : public QThread
{
    Q_OBJECT;
public:
    CommandThread( const int side );

    CommandState* commandState()const;

    bool start(); //asynchronus
    bool pause(); //asynchronus
    bool stop();  //asynchronus

protected:
    void run();

private:
    boost::shared_ptr< CommandThreadImpl > m_impl;
};

//-------------------------------------------------------

#endif //__COMMAND_THREAD__