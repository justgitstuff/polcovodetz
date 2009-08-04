
//-------------------------------------------------------

#include <Core/PObjects/PObject.h>

#include <Core/PObjects/PObjectSharedImpl.h>
#include <Core/PolkApp.h>

#include <QImage>
#include <QThreadStorage>

//-------------------------------------------------------

static volatile qint64 g_uniqueID = 1;

//-------------------------------------------------------

PObject::PObject( const int side )
        :m_objectID( g_uniqueID++ ),
        m_side( side )
{
    s_impl.reset( new PObjectSharedImpl() );
}

//-------------------------------------------------------

bool PObject::init( const QSize& boundingSize )
{
    m_boundingSize = new QSize( boundingSize );

    return true;
}

//-------------------------------------------------------

PObject::~PObject()
{
    delete m_boundingSize;
}

//-------------------------------------------------------

QPoint PObject::position()const
{
    return s_impl->coordinate;
}

//-------------------------------------------------------

