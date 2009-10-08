
//-------------------------------------------------------

#ifndef  __ABSTRACT_P_OBJECT__
#define  __ABSTRACT_P_OBJECT__

//-------------------------------------------------------

#include <boost/shared_ptr.hpp>
#include <QPoint>
#include <QSize>

//-------------------------------------------------------

class AbstractPObject
{
public:

    virtual ~AbstractPObject(){};

    virtual int            rtti()const = 0;
    virtual qint64         objectID()const = 0;


    virtual QSize          boundSize()const = 0;
    virtual int            side()const = 0;

    virtual int            rotation()const = 0;
    virtual QPoint         position()const = 0;
    virtual QPoint         speed()const = 0;

    virtual QPoint         maxSpeed()const = 0;

    virtual bool           canFly()const = 0;
};

//-------------------------------------------------------

typedef boost::shared_ptr< AbstractPObject > PtrAPObject;

//-------------------------------------------------------

#endif //__ABSTRACT_P_OBJECT__

//-------------------------------------------------------

