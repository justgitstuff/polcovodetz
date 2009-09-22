
#include <Core/WinState.h>

//-------------------------------------------------------

struct WinStateImpl
{
    int side;
};

//-------------------------------------------------------

WinState::WinState()
:m_impl( new WinStateImpl() )
{

}

//-------------------------------------------------------

WinState::~WinState()
{

}

//-------------------------------------------------------

int WinState::winner()const
{
    return m_impl->side;
}

//-------------------------------------------------------

void WinState::setWinner( int side )
{
    m_impl->side = side;
}

//-------------------------------------------------------

