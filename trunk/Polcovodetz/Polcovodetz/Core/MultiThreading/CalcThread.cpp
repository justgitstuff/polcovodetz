
//-------------------------------------------------------

#include <Core/MultiThreading/CalcThread.h>

#include <Core/PolkApp.h>

#include <QMutex>

//-------------------------------------------------------

const int SLEEP_TIMEOUT = 25;

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
    QThread::start();

    m_impl->stopped = false;

    return true;
}

//-------------------------------------------------------

void CalcThread::run()
{
    sleep( 1 );

    while( true )
    {
        msleep( SLEEP_TIMEOUT );

        if( !m_impl->stopped )
            pApp.refreshState();
    }
}

//-------------------------------------------------------

