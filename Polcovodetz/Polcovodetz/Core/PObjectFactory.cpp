
//-------------------------------------------------------

#include <Core/PObjectFactory.h>

#include <Core/PObjects/UserObjects/Moving/SimpleTank.h>

#include <QMap>

//-------------------------------------------------------

PObjectFactory pof;

//-------------------------------------------------------

struct PObjectFactoryImpl
{
    typedef QMap< int, PObjectInfo > InfoMap;//Map: PObject RTTI to PObjectInfo

    PObjectInfos    infos;
    InfoMap         infoMap;
};

//-------------------------------------------------------

PObjectFactory::PObjectFactory()
{
    m_impl.reset( new PObjectFactoryImpl() );

    loadInfos();
}

//-------------------------------------------------------

PObjectFactory::~PObjectFactory()
{

}

//-------------------------------------------------------

void PObjectFactory::loadInfos()
{
    m_impl->infoMap.insert( SimpleTank::RTTI, SimpleTank::info() );


    for( PObjectFactoryImpl::InfoMap::ConstIterator iter = m_impl->infoMap.constBegin();
        iter != m_impl->infoMap.constEnd();
        iter++ )
    {
        m_impl->infos.append( iter.value() );
    }
}

//-------------------------------------------------------

PObjectInfo PObjectFactory::pObjectInfo( const int rtti )const
{
    return m_impl->infoMap[ rtti ];
}

//-------------------------------------------------------

const PObjectInfos& PObjectFactory::pObjectInfos()const
{
    return m_impl->infos;
}

//-------------------------------------------------------

