
//-------------------------------------------------------------

#include <GUI/SpecialControls/CrashImageItem.h>

#include <GUI/SpecialControls/Resources/Crash.xpm>

#include <QPixmap>
#include <QVector>

//-------------------------------------------------------------

struct CrashImageItemImpl
{
    QGraphicsItem* innerItem;

    QVector< QPixmap > pictures;

    int currentPicture;
};

//-------------------------------------------------------------

CrashImageItem::CrashImageItem()
    : QGraphicsPixmapItem(), m_impl( new CrashImageItemImpl() )
{
    QPixmap pixmap( crash_xpm );

    while( pixmap.height() > 0 )
    {
        m_impl->pictures.append( pixmap );

        pixmap.scaled( pixmap.size() / 2 );
    }
}

//-------------------------------------------------------------

CrashImageItem::~CrashImageItem()
{

}

//-------------------------------------------------------------

void CrashImageItem::nextStep()
{
    if( m_impl->currentPicture < 1 )
        return;

    m_impl->currentPicture--;

    setPixmap( m_impl->pictures[ m_impl->currentPicture ] );

    return;
}

//-------------------------------------------------------------

