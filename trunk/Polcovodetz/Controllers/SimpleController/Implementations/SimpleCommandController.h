

#ifndef  __SIMPLE_COMMAND_CONTROLLER
#define  __SIMPLE_COMMAND_CONTROLLER

//-------------------------------------------------------

#include <ICommandController.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct SimpleCommandControllerImpl;
class CoreCommandMessage;
class GroupCommandMessage;

//-------------------------------------------------------

/**
    Реализация простейшего ICommandController.

    Реализация самая простейшая, так как класс планируется как образец для 
    написания/тестирование других классов этого уровня.
*/
class SimpleCommandController : public ICommandController
{
    Q_OBJECT;

public:
    SimpleCommandController();

    virtual QString name()const;
    virtual QString description()const;

    virtual bool    init( ICommandInputDriver*, ICommandOutputDriver* );

private:    
    /**
    Прячем часть полей внутрь cpp-шника.
    */
    boost::shared_ptr< SimpleCommandControllerImpl > m_impl;

public slots:
    virtual void message( CoreCommandMessage* );
    virtual void message( GroupCommandMessage* );

};

//-------------------------------------------------------

#endif //__SIMPLE_COMMAND_CONTROLLER

//-------------------------------------------------------

