

#ifndef  __SIMPLE_OBJECT_CONTROLLER
#define  __SIMPLE_OBJECT_CONTROLLER

//-------------------------------------------------------

#include <IObjectController.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct SimpleObjectControllerImpl;

struct ObjectInputMessage;
struct ObjectOutputMessage;

//-------------------------------------------------------

/**
    Реализация простейшего IObjectController.

    Реализация самая простейшая, так как класс планируется как образец для 
    написания/тестирование других классов этого уровня.
*/
class SimpleObjectController : public IObjectController
{
    Q_OBJECT;

public:
    SimpleObjectController();

    virtual QString name()const;
    virtual QString description()const;

    virtual bool    init( IObjectDriver* );

public slots:
    virtual void message( CoreObjectMessage* );
    virtual void message( CommandObjectMessage* ){};
    virtual void message( GroupObjectMessage* );

private:    
    /**
    Прячем часть полей внутрь cpp-шника.
    */
    boost::shared_ptr< SimpleObjectControllerImpl > m_impl;

};

//-------------------------------------------------------

#endif //__SIMPLE_OBJECT_CONTROLLER

//-------------------------------------------------------

