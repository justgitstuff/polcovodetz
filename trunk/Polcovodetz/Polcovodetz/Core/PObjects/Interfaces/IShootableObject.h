
//-------------------------------------------------------

#ifndef  __I_SHOOTABLE_OBJECT__
#define  __I_SHOOTABLE_OBJECT__

//-------------------------------------------------------

//#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

class AbstractRocket;

//-------------------------------------------------------

class IShootableObject
{
public:
    virtual AbstractRocket* atackObject()const    = 0;
    virtual int             shootCount()const     = 0;
    virtual int             maxShootOnPane()const = 0;
};

//-------------------------------------------------------

#endif //__I_SHOOTABLE_OBJECT__

//-------------------------------------------------------

