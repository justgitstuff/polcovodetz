#ifndef __VERSION_INFO_H
#define __VERSION_INFO_H

//-------------------------------------------------------

#include <QString>

//-------------------------------------------------------

class VerionInfo
{
public:
    VerionInfo( int release, int major, int minor, int revision )
    {
        m_release = release;
        m_major = major;
        m_minor = minor;
        m_revision = revision;    
    };

    inline QString toString()const{ return QString( "%1.%2.%3.%4" ).arg( m_release ).arg( m_major ).arg( m_minor ).arg( m_revision ); }

private:
    int m_release;
    int m_major;
    int m_minor;
    int m_revision;    
};

//-------------------------------------------------------

#endif // __VERSION_INFO_H

//-------------------------------------------------------

