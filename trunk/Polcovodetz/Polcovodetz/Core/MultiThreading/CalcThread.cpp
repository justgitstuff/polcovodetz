
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

    QThread::start();
}

//-------------------------------------------------------

bool CalcThread::init()
{
    return true;
}

//-------------------------------------------------------

bool CalcThread::pause()
{
    m_impl->stopped = true;

    return true;
}

//-------------------------------------------------------


bool CalcThread::start()
{
    m_impl->stopped = false;

    return true;
}

//-------------------------------------------------------
void CalcThread::run()
{
    sleep( 1 );

    while( true )
    {
        bool stopped = m_impl->stopped;

        if( stopped )
            sleep( 1 );

        msleep( SLEEP_TIMEOUT );

        if( !stopped )
            pApp.refreshState();
    }
}

//-------------------------------------------------------

