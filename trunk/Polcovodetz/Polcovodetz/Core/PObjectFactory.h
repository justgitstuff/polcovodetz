#ifndef  __POBJECT_FACTORY__
#define  __POBJECT_FACTORY__

//-------------------------------------------------------

#include <QVector>

#include <Core/PObjects/PObject.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct PObjectFactoryImpl;

//-------------------------------------------------------

typedef QVector< PObjectInfo > PObjectInfos;

//-------------------------------------------------------
/** 
     
*/
class PObjectFactory : public QObject
{
    Q_OBJECT;
public:
    PObjectFactory();
    ~PObjectFactory();

    PtrPObject           getPObject( const int rtti );
    PObjectInfo          pObjectInfo( const int rtti )const;
    const PObjectInfos&  pObjectInfos()const;

private:
    boost::shared_ptr< PObjectFactoryImpl > m_impl;   

    void loadInfos();
};

//-------------------------------------------------------

extern PObjectFactory pof;

//-------------------------------------------------------

#endif //__POBJECT_FACTORY__