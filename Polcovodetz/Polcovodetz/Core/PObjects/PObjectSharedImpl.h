
//-------------------------------------------------------

#ifndef  __P_OBJECT_SHARED_IMPL__
#define  __P_OBJECT_SHARED_IMPL__

//-------------------------------------------------------

#include <QPointF>

//-------------------------------------------------------

class PObject;
class PolkApp;

//-------------------------------------------------------

class PObjectSharedImpl
{
    friend class PObject;
    friend class PolkApp;
private:

    QPointF coordinate;
    QPointF speed;
    qreal   rotation;
};

//-------------------------------------------------------

#endif //__P_OBJECT_SHARED_IMPL__

//-------------------------------------------------------

