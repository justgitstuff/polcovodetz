
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

   virtual bool    init( IObjectDriver* );

    /**True, ���� ���������� ������������ ������� ������*/
   virtual bool wantListenKeys()const{ return true; }

public slots:
    virtual void message( CoreObjectMessage* );
    virtual void message( CommandObjectMessage* ){};
    virtual void message( GroupObjectMessage* ){};

public slots:
   virtual void keyPressed( const Qt::Key );


private:
    boost::shared_ptr< HumanObjectControllerImpl > m_impl;
};

//-------------------------------------------------------

#endif

//-------------------------------------------------------

