

#ifndef  __MESSAGES
#define  __MESSAGES

//-------------------------------------------------------

#include <AbstractMessage.h>
#include <qglobal.h>
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
};
//-------------------------------------------------------
/**
    Класс - сообщение от главного командира к ядру
*/
class CommandCoreMessage : public AbstractMessage
{
    enum Type 
    { };
};

//-------------------------------------------------------
/**
    Класс - сообщение от коммандующего группой к главному командиру
*/
class GroupCommandMessage : public AbstractMessage
{
    enum Type 
    {
        GameStarted
    };

};
//-------------------------------------------------------
/**
    Класс - сообщение от главного командира к коммандующего группой
*/
class CommandGroupMessage : public AbstractMessage
{
    enum Type 
    { };
};

//-------------------------------------------------------
/**
    Класс - сообщение от коммандующего группой к командиру объекта
*/
class GroupObjectMessage : public AbstractMessage
{
    enum Type 
    {
        GameStarted
    };

};
//-------------------------------------------------------
/**
    Класс - сообщение от командира объекта к командиру группы
*/
class ObjectGroupMessage : public AbstractMessage
{
    enum Type 
    { };
};

//-------------------------------------------------------

#endif //__MESSAGES

//-------------------------------------------------------

