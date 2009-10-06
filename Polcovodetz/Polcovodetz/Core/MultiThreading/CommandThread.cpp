
//-------------------------------------------------------

#include <Core/MultiThreading/CommandThread.h>

#include <Core/MultiThreading/CommandState.h>

#include <QApplication>

//-------------------------------------------------------

struct CommandThreadImpl
{
    CommandThreadImpl() : state( 0 ), paused( true ){}

    bool paused;

    int side;

    CommandState* state;
};

//-------------------------------------------------------

CommandThread::CommandThread( const int side )
:QThread(), m_impl( new CommandThreadImpl() )
{
    m_impl->side = side;

    QThread::start();
}

//-------------------------------------------------------

bool CommandThread::start()
{
    m_impl->paused = false;

    return true;
}

//-------------------------------------------------------

bool CommandThread::pause()
{    
    m_impl->paused = true;

    return true;
}

//-------------------------------------------------------

CommandState* CommandThread::commandState()const
{
    return m_impl->state;
}

//-------------------------------------------------------

void CommandThread::run()
{
    m_impl->state = new CommandState( m_impl->side );

    while( m_impl->paused )
        QThread::sleep( 1 );

    m_impl->state->connectDrivers();

    int sleepIndex = 0;

    while( 1 )
    {
        sleepIndex++;

        if( m_impl->paused )
        {
            QThread::msleep( 1000 );

            continue;
        }

        m_impl->state->sendInnerMessages();

        qApp->processEvents();

        QThread::msleep( 25 );

        if( sleepIndex % 2 )
        {
            m_impl->state->updatePositions( true );
        }
    }
    return;
}
