
//-------------------------------------------------------

#ifndef  __P_OBJECT__
#define  __P_OBJECT__

//-------------------------------------------------------

#include <AbstractPObject.h>
#include <QString>

//-------------------------------------------------------

class PObjectSharedImpl;

class QSize;
class QPixmap;
class QPoint;

/**
    Хранит инфорацию об экземпляре PObject.
    Может пригодиться для отражения в GUI.

    ToDo: добавить поля "максимальная скорость", "размеры" и пр.
*/
struct PObjectInfo
{
    int     id;
    QString name;
    QString description;
};

//-------------------------------------------------------

class PObject : public AbstractPObject
{
public:

    enum OnCollision
    {
        Nothing        = 0,
        Revert         = 1 << 0,
        DisposeMyself  = 1 << 1,
        DisposeAnother = 1 << 2,
        DisposeTwice   = DisposeMyself | DisposeAnother
    };

    PObject( int side, qint64 parentID = -1 );

  //  PObject& operator=( const PObject & ) {};

    virtual ~PObject();

    virtual int            rtti()const = 0;

    virtual QSize          boundSize()const = 0;
            qint64         objectID()const{ return m_objectID; }
            qint64         parentID()const{ return m_parentID; }
            int            side()const{ return m_side; }

    virtual int            rotation()const;
    virtual QPoint         position()const;
    virtual QPoint         speed()const;

    virtual QPoint         maxSpeed()const = 0;

    virtual bool           canFly()const = 0;
    virtual bool           needManagement()const = 0;
    virtual OnCollision    onCollision()const = 0;

    /**
        Когда объект столкнулся со строением на карте.
    */
    virtual OnCollision    onStop()const = 0;

    virtual const QPixmap& image()const = 0;

                  QPixmap  image( const int angle );

    PObjectSharedImpl*     sImpl()const{ return s_impl.get(); }

private:
    qint64 m_objectID;
    int    m_side;
    qint64 m_parentID;

    boost::shared_ptr< PObjectSharedImpl > s_impl;
};

//-------------------------------------------------------

typedef boost::shared_ptr< PObject > PtrPObject;

//-------------------------------------------------------

#endif //__P_OBJECT__

//-------------------------------------------------------

