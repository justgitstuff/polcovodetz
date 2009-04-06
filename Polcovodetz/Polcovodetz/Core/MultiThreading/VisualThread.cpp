
//-------------------------------------------------------

#include <Core/MultiThreading/VisualThread.h>

#include <QMutex>

//-------------------------------------------------------

const int SLEEP_TIMEOUT = 50;

//-------------------------------------------------------

struct VisualThreadImpl
{
    BattleState* battleState;

    QMutex       pauseLocker;

    bool         stopped;
};

//-------------------------------------------------------

VisualThread::VisualThread()
            :QThread()
{
    m_impl.reset( new VisualThreadImpl() );

    m_impl->stopped = true;
}

//-------------------------------------------------------

bool VisualThread::init( BattleState* battle )
{
    m_impl->battleState = battle;

    return true;
}

//-------------------------------------------------------

bool VisualThread::start()
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

