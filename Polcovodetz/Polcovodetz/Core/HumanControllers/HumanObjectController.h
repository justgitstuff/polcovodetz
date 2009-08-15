
//-------------------------------------------------------

#ifndef __HUMAN_OBJECT_CONTROLLER_
#define __HUMAN_OBJECT_CONTROLLER_

//-------------------------------------------------------

#include <IObjectController.h>
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------

struct HumanObjectControllerImpl;
class  ObjectInputMessage;

//-------------------------------------------------------

class HumanObjectController : IObjectController
{
public:
                   HumanObjectController();

   virtual QString name()const;
   virtual QString description()const;

   virtual bool    init( IObjectInputDriver*, IObjectOutputDriver* );

public slots:
   void HumanObjectController::inputMessage( ObjectInputMessage* /*mesage*/ );

private:
    boost::shared_ptr< HumanObjectControllerImpl > m_impl;
};

//-------------------------------------------------------

#endif

//-------------------------------------------------------

