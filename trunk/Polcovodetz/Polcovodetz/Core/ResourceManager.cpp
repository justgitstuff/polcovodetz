
//-------------------------------------------------------

#include <Core/ResourceManager.h>

#include <GUI/SpecialControls/Resources/CommandImage.xpm>
#include <GUI/SpecialControls/Resources/GroupImage.xpm>
#include <GUI/SpecialControls/Resources/ObjectImage.xpm>
#include <GUI/SpecialControls/Resources/Refresh.xpm>

#include <QPixmap>
#include <QVector>

//-------------------------------------------------------

ResourceManager resMan;

//-------------------------------------------------------

struct ResourceManagerImpl
{
    QVector< QPixmap > images;
};

//-------------------------------------------------------

ResourceManager::ResourceManager()
{
    m_impl.reset( new ResourceManagerImpl() );
}

//-------------------------------------------------------

ResourceManager::~ResourceManager()
{ }

//-------------------------------------------------------

void ResourceManager::loadPicturies()
{
    m_impl->images.resize( _count );

    m_impl->images[ Command ] = QPixmap( commandimage_xpm );
    m_impl->images[ Group ]   = QPixmap( groupimage_xpm );
    m_impl->images[ Object ]  = QPixmap( objectimage_xpm );
    m_impl->images[ Refresh ] = QPixmap( refresh_xpm );
}

//-------------------------------------------------------

const QPixmap& ResourceManager::image( const Picturies pict )
{
    static QPixmap EMPTY;

    if( m_impl->images.size() == 0 )
        loadPicturies();

    if( pict == _count )
        return EMPTY;

    return m_impl->images[ pict ];
}

//-------------------------------------------------------

