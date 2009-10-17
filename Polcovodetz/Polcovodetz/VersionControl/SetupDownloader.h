#ifndef SETUPDOWNLOADER_H
#define SETUPDOWNLOADER_H

//-------------------------------------------------------

#include <QObject>

#include <VersionControl/VersionInfo.h>

#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct SetupDownloaderImpl;

//-------------------------------------------------------

class SetupDownloader : public QObject
{
    Q_OBJECT

public:
    SetupDownloader();
    ~SetupDownloader();


    VerionInfo version()const;

public slots:
    bool       loadSettings();
    
private slots:
    void       onConnect();

private:
    boost::shared_ptr< SetupDownloaderImpl > m_impl;
};

//-------------------------------------------------------

#endif // SETUPDOWNLOADER_H

//-------------------------------------------------------

