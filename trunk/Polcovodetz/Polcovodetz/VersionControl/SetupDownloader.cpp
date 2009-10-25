
//-------------------------------------------------------

#include <VersionControl/SetupDownloader.h>

#include <QHostAddress>
#include <QTcpSocket>

//-------------------------------------------------------

struct SetupDownloaderImpl
{
    static const int   DEFAULT_PORT = 10000;    

    QTcpSocket socket;
};

//-------------------------------------------------------

SetupDownloader::SetupDownloader()
: QObject(), m_impl( new SetupDownloaderImpl() )
{

}

//-------------------------------------------------------

SetupDownloader::~SetupDownloader()
{

}

//-------------------------------------------------------

bool SetupDownloader::loadSettings()
{
    m_impl->socket.connectToHost( "85.249.78.60", SetupDownloaderImpl::DEFAULT_PORT );

    m_impl->socket.waitForConnected();

    if( m_impl->socket.state() != QAbstractSocket::ConnectedState )
    {
        m_impl->socket.close();

        return false;
    }

    //m_impl->
        
    return false;
}

//-------------------------------------------------------

void SetupDownloader::onConnect()
{

}

//-------------------------------------------------------

