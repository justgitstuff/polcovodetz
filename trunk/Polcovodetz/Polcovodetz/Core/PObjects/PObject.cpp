
//-------------------------------------------------------

#include <Core/PObjects/PObject.h>

#include <Core/PObjects/PObjectSharedImpl.h>
#include <Core/PolkApp.h>

#include <QImage>
#include <QPixmap>
#include <QThreadStorage>

//-------------------------------------------------------

static volatile qint64 g_uniqueID = 1;

//-------------------------------------------------------

PObject::PObject( const int side, const qint64 parentID )
        :m_objectID( g_uniqueID++ ),
        m_side( side ),
        m_parentID( parentID )
{
    s_impl.reset( new PObjectSharedImpl() );

    s_impl->speed = QPoint( 0, 0 );
    s_impl->rotation = 0;
    s_impl->coordinate = QPoint( 0, 0 );
}

//-------------------------------------------------------

PObject::~PObject()
{
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

QPixmap PObject::image( const int angle )
{
    const QPixmap& img = image();

    switch( angle )
    {
    case 90:
        {
            return img.transformed( QMatrix( 0, -1, -1, 0, 1, 1 ) );
            break;
        }
    case 270:
        {
            return img.transformed( QMatrix( 0, 1, 1, 0, 1, 1 ) );
            break;
        }
    case 180:
        {
            return img.transformed( QMatrix( -1, 0, 0, -1, 1, 1 ) );
            break;
        }
    }

    return QPixmap( img );
}

//-------------------------------------------------------

