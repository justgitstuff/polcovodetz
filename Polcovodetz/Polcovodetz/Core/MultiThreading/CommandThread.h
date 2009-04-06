
#ifndef  __COMMAND_THREAD__
#define  __COMMAND_THREAD__

//-------------------------------------------------------

#include <QThread>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct CommandThreadImpl;

//-------------------------------------------------------

class CommandThread : public QThread
{
    Q_OBJECT;
public:
    CommandThread();

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