#ifndef __DRIVER_HELPER_H
#define __DRIVER_HELPER_H

//-------------------------------------------------------

#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct DriverHelperImpl;

class Map;
class MapOperations;

//-------------------------------------------------------

class DriverHelper 
{
public:
    DriverHelper( const Map& );
    ~DriverHelper();

    MapOperations* mapOperations()const;

private:
    boost::shared_ptr< DriverHelperImpl > m_impl;
    
};

//-------------------------------------------------------

#endif // __DRIVER_HELPER_H

//-------------------------------------------------------

