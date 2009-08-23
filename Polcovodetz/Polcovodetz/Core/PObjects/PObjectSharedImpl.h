
//-------------------------------------------------------

#ifndef  __P_OBJECT_SHARED_IMPL__
#define  __P_OBJECT_SHARED_IMPL__

//-------------------------------------------------------

#include <QPoint>

//-------------------------------------------------------

class PObject;
class PolkApp;

//-------------------------------------------------------

class PObjectSharedImpl
{
    friend class PObject;
    friend class PolkApp;
private:

    QPoint  coordinate;
    QPoint  speed;

    /**
        �������. �� 0 �� 360
    */
    int     rotation;
};

//-------------------------------------------------------

#endif //__P_OBJECT_SHARED_IMPL__

//-------------------------------------------------------

