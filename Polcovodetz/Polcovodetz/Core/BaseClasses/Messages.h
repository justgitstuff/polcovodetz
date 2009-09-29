

#ifndef  __MESSAGES
#define  __MESSAGES

//-------------------------------------------------------

#include <AbstractMessage.h>
#include <QPoint>

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
    CoreObjectMessage( int id ): AbstractMessage( id ){}

    enum Type 
    {
        /**
            Смена квадрата.
            В поле point выставляется предыдущее значение.
        */
        SquareChanged,

        /**
            При создании нового объекта.
        */
        Recreated
    };

    QPoint  point;

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
    { };

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
        GameStarted
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
        GameStarted
    };

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

