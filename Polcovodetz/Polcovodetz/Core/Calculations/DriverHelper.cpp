
//-------------------------------------------------------

#include <Core/Calculations/DriverHelper.h>

#include <Core/Calculations/MapOperations.h>

//-------------------------------------------------------

struct DriverHelperImpl
{
    boost::shared_ptr< MapOperations > mapOperations;
};

//-------------------------------------------------------

DriverHelper::DriverHelper( const Map& map )
:m_impl( new DriverHelperImpl )
{
    m_impl->mapOperations.reset( new MapOperations( map ) );
}

//-------------------------------------------------------

DriverHelper::~DriverHelper()
{

}

//-------------------------------------------------------

MapOperations* DriverHelper::mapOperations() const
{
    return m_impl->mapOperations.get();
}

//-------------------------------------------------------

