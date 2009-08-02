#ifndef  __LIBRARY_LOADER__
#define  __LIBRARY_LOADER__

//-------------------------------------------------------

#include <QObject>
#include <QString>
#include <QList>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct LibraryLoaderImpl;

class QWidget;

class ICommandController;
class IGroupController;
class IObjectController;

//-------------------------------------------------------
/**
    Хранит инфорацию о подгружаемой библиотеке.
*/
struct LibDefinition
{
    int     id;

    QString name;
    QString descritpion;

    QString ccName;
    QString ccDescription;
    QString gcName;
    QString gcDescription;
    QString ocName;
    QString ocDescription;
};

//-------------------------------------------------------
/** 
     Менеджер ресурсов для проекта.
*/
class LibraryLoader : public QObject
{
    Q_OBJECT;
public:

    typedef const QList< LibDefinition > LibDefinitions;

    LibraryLoader();
    ~LibraryLoader();
    
    QWidget*            loadInfoView()const;
    int                 loadLibrary( const QString& fileName );

    LibDefinitions      loadedLibraries()const;
    LibDefinition       library( const int id )const;

    ICommandController* loadCommandController( const int libraryID );
    IGroupController*   loadGroupController( const int libraryID );
    IObjectController*  loadObjectController( const int libraryID );

signals:
    void          newLibrary( const LibDefinition& );

private:
    boost::shared_ptr< LibraryLoaderImpl > m_impl;   

};

//-------------------------------------------------------

extern LibraryLoader libLoader;

//-------------------------------------------------------

#endif //__LIBRARY_LOADER__