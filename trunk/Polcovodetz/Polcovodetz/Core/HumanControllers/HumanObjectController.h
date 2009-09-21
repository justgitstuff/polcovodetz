
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

class HumanObjectController : public IObjectController
{
public:
                   HumanObjectController();

   virtual QString name()const;
   virtual QString description()const;

   virtual bool    init( IObjectInputDriver*, IObjectOutputDriver* );

    /**True, если собираемся обрабатывать нажатия клавиш*/
   virtual bool wantListenKeys()const{ return true; }

public slots:
    virtual void message( GroupObjectMessage* );

public slots:
   virtual void keyPressed( const Qt::Key );


private:
    boost::shared_ptr< HumanObjectControllerImpl > m_impl;
};

//-------------------------------------------------------

#endif

//-------------------------------------------------------

