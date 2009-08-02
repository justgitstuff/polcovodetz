
//-------------------------------------------------------

#include <Core/MultiThreading/CalcThread.h>

#include <QMutex>

//-------------------------------------------------------

const int SLEEP_TIMEOUT = 50;

//-------------------------------------------------------

struct CalcThreadImpl
{
    BattleState* battleState;

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

bool CalcThread::init( BattleState* battle )
{
    m_impl->battleState = battle;

    return true;
}

//-------------------------------------------------------

bool CalcThread::start()
{
    m_impl->stopped = false;

    return false;
}

//-------------------------------------------------------

void VisualThread::run()
{
    while( !m_impl->stopped )
    {
/*        BattleState* battle = m_impl->battleState;

        BattleState::ActiveObjects = battle->objects();*/

        msleep( SLEEP_TIMEOUT );
    }
}

//-------------------------------------------------------

