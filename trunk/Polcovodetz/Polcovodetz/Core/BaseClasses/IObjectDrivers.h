

#ifndef  __IOBJECT_DRIVERS
#define  __IOBJECT_DRIVERS

//-------------------------------------------------------

#include <IAbstractDrivers.h>
#include <AbstractPObject.h>
#include <MovementDirection.h>

#include <QPoint>

//-------------------------------------------------------

class IObjectController;

//-------------------------------------------------------

enum ObjectRotation
{ 
    ToTop, 
    ToBottom, 
    ToLeft, 
    ToRight 
};

//-------------------------------------------------------
/**
    Драйвер
*/
class IObjectDriver : public IAbstractInputDriver
{
    Q_OBJECT;

public:
    virtual MovementDirection nearesPointToFlag()const = 0;

    virtual PtrAPObject pObject()const = 0;

    /**
        Устанавливает скорость как процент от максимальной.
        Значения - от 0 до 100
    */
    virtual void setSpeed( const int persent ) = 0;

    /**
        Устанавливает текущий поворот объекта
    */
    virtual void setRotation( const ObjectRotation& rotation ) = 0;
    virtual void setRotation( const MovementDirection& rotation ) = 0;
   
    /**
        Выпускает снаряд
    */
    virtual void makeAttack() = 0;

    /**
        Переводит из глобальных координат в номер квадрата
    */
    virtual QPoint convertToNumber( const QPoint& bigCoordinates )const = 0;
    QPoint convertToNumber( int x, int y )const{ return convertToNumber( QPoint( x, y ) ); }

    /**
        Переводит из номера квадрата в глобальные координаты.
        На выходе будет наименьшие возможные координаты (x,y), такие,
        что convertToNumber( convertToCoordinate( point ) ) == point.
    */
    virtual QPoint convertToCoordinate( const QPoint& squareNumber )const = 0;
    QPoint convertToCoordinate( int x, int y )const{ return convertToCoordinate( QPoint( x, y ) ); }


    virtual MovementDirection getRandomRotation()const = 0;

};

//-------------------------------------------------------

#endif //__IOBJECT_DRIVERS

//-------------------------------------------------------

