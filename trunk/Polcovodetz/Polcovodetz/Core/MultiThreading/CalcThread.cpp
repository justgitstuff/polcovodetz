
//-------------------------------------------------------

#include <Core/MultiThreading/CalcThread.h>

#include <QMutex>

//-------------------------------------------------------

const int SLEEP_TIMEOUT = 50;

//-------------------------------------------------------

struct CalcThreadImpl
{
   // BattleState* battleState;

    QMutex       pauseLocker;

    bool         stopped;
};

//-------------------------------------------------------

CalcThread::CalcThread()
            :QThread()
{
    m_impl.reset( new CalcThreadImpl() );

    m_impl->stopped = true;
}

//-------------------------------------------------------

bool CalcThread::init()
{
    return true;
}

//-------------------------------------------------------

bool CalcThread::start()
{
    return false;
}

//-------------------------------------------------------

void CalcThread::run()
{
    while( !m_impl->stopped )
    {

        msleep( SLEEP_TIMEOUT );
    }
}

//-------------------------------------------------------

