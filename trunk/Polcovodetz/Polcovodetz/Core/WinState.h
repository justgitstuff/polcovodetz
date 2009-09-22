#ifndef __WINSTATE_H
#define __WINSTATE_H

//-------------------------------------------------------

#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct WinStateImpl;

//-------------------------------------------------------

class WinState
{
public:
    WinState();
    ~WinState();

    int  winner()const;
    void setWinner( int );

private:
    boost::shared_ptr< WinStateImpl > m_impl;   

};

//-------------------------------------------------------

#endif // __WINSTATE_H
