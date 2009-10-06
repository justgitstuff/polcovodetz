#ifndef POSITIONMANAGER_H
#define POSITIONMANAGER_H

//-------------------------------------------------------

#include <PObject.h>

#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

class  CommandState;
struct PositionManagerImpl;

//-------------------------------------------------------

class PositionManager
{
public:
    PositionManager( CommandState* command1, CommandState* command2 );
    ~PositionManager();

    void addObject( const PtrPObject& );
    void deleteObject( qint64 id );

    void checkObjects();

private:
    boost::shared_ptr< PositionManagerImpl > m_impl;
};

//-------------------------------------------------------

#endif // POSITIONMANAGER_H

//-------------------------------------------------------

