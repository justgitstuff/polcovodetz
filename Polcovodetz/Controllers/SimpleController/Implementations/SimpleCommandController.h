

#ifndef  __SIMPLE_COMMAND_CONTROLLER
#define  __SIMPLE_COMMAND_CONTROLLER

//-------------------------------------------------------

#include <ICommandController.h>

//-------------------------------------------------------

class SimpleCommandController : public ICommandController
{
    Q_OBJECT;

public:
    SimpleCommandController();

    virtual QString name()const;
    virtual QString description()const;

    virtual bool    init( ICommandInputDriver*, ICommandOutputDriver* );

};

//-------------------------------------------------------

#endif //__SIMPLE_COMMAND_CONTROLLER

//-------------------------------------------------------

