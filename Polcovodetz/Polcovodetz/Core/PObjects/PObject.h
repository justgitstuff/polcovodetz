
//-------------------------------------------------------

#ifndef  __P_OBJECT__
#define  __P_OBJECT__

//-------------------------------------------------------

#include <QObject>
#include <QString>
#include <boost/shared_ptr.hpp>

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

class PObject : QObject
{
    Q_OBJECT;

public:
    PObject( const int side );

    bool init( const QSize& );

    virtual ~PObject();

    virtual int  rtti()const = 0;

    const QSize& boundSize()const;
          qint64 objectID()const{ return m_objectID; }
          int    side()const{ return m_side; }

    int          rotation()const;
    QPoint       position()const;
    QPoint       speed()const;

    virtual QPoint maxSpeed()const = 0;

    bool         canFly()const{ return false; }

    virtual const QPixmap& image()const = 0;

    PObjectSharedImpl* sImpl()const{ return s_impl.get(); }

private:
    QSize*       m_boundingSize;

    const qint64 m_objectID;
    const int    m_side;

    boost::shared_ptr< PObjectSharedImpl > s_impl;
};

//-------------------------------------------------------

typedef boost::shared_ptr< PObject > PtrPObject;

//-------------------------------------------------------

#endif //__P_OBJECT__

//-------------------------------------------------------

