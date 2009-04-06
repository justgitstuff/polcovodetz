

#ifndef  __SIMPLE_COMMAND_CONTROLLER
#define  __SIMPLE_COMMAND_CONTROLLER

//-------------------------------------------------------

#include <ICommandController.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct SimpleCommandControllerImpl;

struct CommandInputMessage;
struct CommandOutputMessage;

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

signals:
    void outputMessage( CommandOutputMessage* mesage );

private:    
    /**
    Прячем часть полей внутрь cpp-шника.
    */
    boost::shared_ptr< SimpleCommandControllerImpl > m_impl;

private slots:
    void inputMessage( CommandInputMessage* mesage );

};

//-------------------------------------------------------

#endif //__SIMPLE_COMMAND_CONTROLLER

//-------------------------------------------------------

