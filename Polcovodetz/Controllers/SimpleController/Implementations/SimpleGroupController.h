

#ifndef  __SIMPLE_GROUP_CONTROLLER
#define  __SIMPLE_GROUP_CONTROLLER

//-------------------------------------------------------

#include <IGroupController.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct SimpleGroupControllerImpl;

struct GroupInputMessage;
struct GroupOutputMessage;

//-------------------------------------------------------

/**
    Реализация простейшего IGroupController.

    Реализация самая простейшая, так как класс планируется как образец для 
    написания/тестирование других классов этого уровня.
*/
class SimpleGroupController : public IGroupController
{
    Q_OBJECT;

public:
    SimpleGroupController();

    virtual QString name()const;
    virtual QString description()const;

    virtual bool    init( IGroupInputDriver*, IGroupOutputDriver* );

private:    
    /**
    Прячем часть полей внутрь cpp-шника.
    */
    boost::shared_ptr< SimpleGroupControllerImpl > m_impl;

public slots:
    virtual void message( ObjectGroupMessage* ){};
    virtual void message( CommandGroupMessage* ){};

};

//-------------------------------------------------------

#endif //__SIMPLE_GROUP_CONTROLLER

//-------------------------------------------------------

