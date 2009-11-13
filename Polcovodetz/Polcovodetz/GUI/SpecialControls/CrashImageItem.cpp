
//-------------------------------------------------------------

#include <GUI/SpecialControls/CrashImageItem.h>

#include <GUI/SpecialControls/Resources/CrashItems/Crash_1.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_2.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_3.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_4.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_5.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_6.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_7.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_8.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_9.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_10.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_11.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_12.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_13.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_14.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_15.xpm>
#include <GUI/SpecialControls/Resources/CrashItems/Crash_16.xpm>


#include <QPixmap>
#include <QVector>

//-------------------------------------------------------------

typedef QVector< QPixmap > Pixmaps;

//-------------------------------------------------------------

Pixmaps createPixmapVector()
{
    Pixmaps result;

    result.append( QPixmap( crash_1_xpm ) );
    result.append( QPixmap( crash_2_xpm ) );
    result.append( QPixmap( crash_3_xpm ) );
    result.append( QPixmap( crash_4_xpm ) );
    result.append( QPixmap( crash_5_xpm ) );
    result.append( QPixmap( crash_6_xpm ) );
    result.append( QPixmap( crash_7_xpm ) );
    result.append( QPixmap( crash_8_xpm ) );
    result.append( QPixmap( crash_9_xpm ) );
    result.append( QPixmap( crash_10_xpm ) );
    result.append( QPixmap( crash_11_xpm ) );
    result.append( QPixmap( crash_12_xpm ) );
    result.append( QPixmap( crash_13_xpm ) );
    result.append( QPixmap( crash_14_xpm ) );
    result.append( QPixmap( crash_15_xpm ) );
    result.append( QPixmap( crash_16_xpm ) );

    return result;
}


//-------------------------------------------------------------

struct CrashImageItemImpl
{
    static const int PICTURE_DELAY = 1;

    QGraphicsItem* innerItem;

    Pixmaps        pictures;

    int currentPicture;
};

//-------------------------------------------------------------

CrashImageItem::CrashImageItem( QGraphicsScene* parent )
    : QGraphicsPixmapItem( 0, parent ), m_impl( new CrashImageItemImpl() )
{
    static Pixmaps pixmaps = createPixmapVector();

    m_impl->pictures = pixmaps;
    m_impl->currentPicture = -1;

    setZValue( 1 );
}

//-------------------------------------------------------------

CrashImageItem::~CrashImageItem()
{

}

//-------------------------------------------------------------

void CrashImageItem::nextStep()
{
    m_impl->currentPicture++;

    if( m_impl->currentPicture >= m_impl->pictures.size() )
        return;

    setPixmap( m_impl->pictures[ m_impl->currentPicture ] );

    return;
}

//-------------------------------------------------------------

bool CrashImageItem::needDelete()const
{
    return m_impl->currentPicture >= m_impl->pictures.size();
}

//-------------------------------------------------------------

