
#ifndef  __VISUAL_THREAD__
#define  __VISUAL_THREAD__

//-------------------------------------------------------

#include <QThread>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct VisualThreadImpl;

class BattleState;

//-------------------------------------------------------
//Рассчитывает скорости и т. п.
class CalcThread : public QThread
{
    Q_OBJECT;
public:
    VisualThread();

    bool init( BattleState* );

    bool start(); //asynchronus
    bool pause(); //asynchronus
    bool stop();  //asynchronus

protected:
    void run();

private:
    boost::shared_ptr< VisualThreadImpl > m_impl;          
};

//-------------------------------------------------------

#endif //__VISUAL_THREAD__