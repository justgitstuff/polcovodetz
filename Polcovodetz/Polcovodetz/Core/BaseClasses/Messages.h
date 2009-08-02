

#ifndef  __MESSAGES
#define  __MESSAGES

//-------------------------------------------------------

#include <AbstractMessage.h>

//-------------------------------------------------------
/**
    Класс - сообщение от ядра к главному командиру
*/
class CoreCommandMessage : public AbstractMessage
{
public:
    enum Type 
    {
        GameStarted
    };

    CoreCommandMessage( Type type )        
    {
        this->type = type;
    }

    Type type;
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

#endif //__MESSAGES

//-------------------------------------------------------

