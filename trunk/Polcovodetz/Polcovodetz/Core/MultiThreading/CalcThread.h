
#ifndef  __VISUAL_THREAD__
#define  __VISUAL_THREAD__

//-------------------------------------------------------

#include <QThread>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct CalcThreadImpl;

//-------------------------------------------------------
//Рассчитывает скорости и т. п.
class CalcThread : public QThread
{
    Q_OBJECT;
public:
    CalcThread();

    bool init();

    bool start(); //asynchronus
    bool pause(); //asynchronus
    bool stop(){ return pause(); } //asynchronus

protected:
    void run();

private:
    boost::shared_ptr< CalcThreadImpl > m_impl;          
};

//-------------------------------------------------------

#endif //__VISUAL_THREAD__