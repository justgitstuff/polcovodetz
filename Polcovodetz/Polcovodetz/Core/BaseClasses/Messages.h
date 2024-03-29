﻿

#ifndef  __MESSAGES
#define  __MESSAGES

//-------------------------------------------------------

#include <AbstractMessage.h>
#include <QPoint>
#include <QRect>

//-------------------------------------------------------
/**
    Класс - сообщение от ядра к главному командиру
*/
class CoreCommandMessage : public AbstractMessage
{
public:
    enum Type 
    {
        GameStarted,
        ObjectCrached
    };

    CoreCommandMessage( Type type )
        : who( -1 ), point( -1, -1 ), objectRTTI( -1 )
    {
        this->type = type;
    }

    Type     type;

    int      objectRTTI;
    qint64   who;
    QPoint   point;

    virtual int rtti()const{ return RTTI; }

    static const int RTTI = 1;
};

//-------------------------------------------------------

class CoreGroupMessage : public AbstractMessage
{
public:

    virtual int rtti()const{ return RTTI; }

    static const int RTTI = 2;
};

//-------------------------------------------------------
/**
    Класс - ядра к объекту
*/
class CoreObjectMessage : public AbstractMessage
{
public:
    CoreObjectMessage( qint64 driverID ): AbstractMessage( driverID ){}

    enum Type 
    {
        /**
            Смена квадрата: объект въехал в новый квадрат ( хотя бы часть объекта теперь содержится в новом квадрате )
        */
        SquareInChanged,

        /**
            Смена квадрата: объект выехал в новый квадрат ( хотя бы часть объекта теперь содержится в новом квадрате )
        */
        SquareOutChanged,

        /**
            При создании нового объекта.
        */
        Recreated,

        /**
            В случае, если объект довольно долго стоит на месте.
        */
        Staying,

        /**
            В случае, если объект заблокирован преградой.
        */
        Blocked
    };

    QPoint  point;

    Type    type;

    virtual int rtti()const{ return RTTI; }

    static const int RTTI = 3;
};

//-------------------------------------------------------
/**
    Класс - сообщение от главного командира к коммандующего группой
*/
class CommandGroupMessage : public AbstractMessage
{
 public:
   enum Type 
   {
       FlagProtection,
       Attack
   };

   Type   type;

    virtual int rtti()const{ return RTTI; }

    static const int RTTI = 4;
};

//-------------------------------------------------------
/**
    
*/
class CommandObjectMessage : public AbstractMessage
{
public:
    enum Type 
    { };

    virtual int rtti()const{ return RTTI; }

    static const int RTTI = 5;
};


//-------------------------------------------------------
/**
    Класс - сообщение от коммандующего группой к главному командиру
*/
class GroupCommandMessage : public AbstractMessage
{
public:
    enum Type 
    {
        
    };

    virtual int rtti()const{ return RTTI; }

    static const int RTTI = 6;
};

//-------------------------------------------------------
/**
    Класс - сообщение от коммандующего группой к командиру объекта
*/
class GroupObjectMessage : public AbstractMessage
{
public:
    enum Type 
    {
        /**
            Патрулирование некоторого прямогугольника.
            В поле rect записывается квадрат патрулирования. Записывается
            не в глобальных координатах, а в сокращенных, т. е. прямогольник будет содержать не 
            координаты точки, а номера квадрата.
        */
        PatrolSquare,

        /**
            Приказывает объекту идти и атаковать флаг
        */
        GoToFlag
    };

    Type  type;

    QRect rect;

    virtual int rtti()const{ return RTTI; }

    static const int RTTI = 7;
};

//-------------------------------------------------------
/**
    Класс - сообщение от командира объекта к командиру группы
*/
class ObjectGroupMessage : public AbstractMessage
{
public:
    enum Type 
    { };

    virtual int rtti()const{ return RTTI; }

    static const int RTTI = 8;
};

//-------------------------------------------------------

class ObjectCommandMessage : public AbstractMessage
{
public:
    enum Type 
    { };

    virtual int rtti()const{ return RTTI; }

    static const int RTTI = 9;
};

//-------------------------------------------------------

#endif //__MESSAGES

//-------------------------------------------------------

