#ifndef  __RESOURCE_MANAGER__
#define  __RESOURCE_MANAGER__

//-------------------------------------------------------

#include <Core/PObjects/PObject.h>
#include <boost/shared_ptr.hpp>

#include <QVector>
#include <QObject>

//-------------------------------------------------------

struct ResourceManagerImpl;
class  QPixmap;

//-------------------------------------------------------
/** 
     Менеджер ресурсов для проекта.
*/
class ResourceManager : public QObject
{
    Q_OBJECT;
public:

    enum Picturies 
    {
        Command = 0,
        Group,
        Object,
        Refresh,
        _count
    };

    ResourceManager();
    ~ResourceManager();

    const QPixmap& image( const Picturies pict );

private:
    boost::shared_ptr< ResourceManagerImpl > m_impl;   

    void loadPicturies();
};

//-------------------------------------------------------

extern ResourceManager resMan;

//-------------------------------------------------------

#endif //__RESOURCE_MANAGER__