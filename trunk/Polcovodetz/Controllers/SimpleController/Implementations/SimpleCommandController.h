

#ifndef  __SIMPLE_COMMAND_CONTROLLER
#define  __SIMPLE_COMMAND_CONTROLLER

//-------------------------------------------------------

#include <ICommandController.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct SimpleCommandControllerImpl;

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
};

//-------------------------------------------------------

#endif //__SIMPLE_COMMAND_CONTROLLER

//-------------------------------------------------------

