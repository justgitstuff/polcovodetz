

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

    virtual bool    init( IObjectInputDriver*, IObjectOutputDriver* );

signals:
    void outputMessage( ObjectOutputMessage* mesage );

private:    
    /**
    Прячем часть полей внутрь cpp-шника.
    */
    boost::shared_ptr< SimpleObjectControllerImpl > m_impl;

private slots:
    void inputMessage( ObjectInputMessage* mesage );

};

//-------------------------------------------------------

#endif //__SIMPLE_OBJECT_CONTROLLER

//-------------------------------------------------------

