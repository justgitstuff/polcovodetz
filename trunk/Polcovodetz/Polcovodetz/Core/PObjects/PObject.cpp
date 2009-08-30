
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

    s_impl->speed = QPoint( 0, 0 );
    s_impl->rotation = 0;
    s_impl->coordinate = QPoint( 0, 0 );
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

QPoint PObject::maxSpeed()const
{
    return QPoint( 1, 1 );
}

//-------------------------------------------------------

int PObject::rotation()const
{
    return s_impl->rotation;
}

//-------------------------------------------------------

