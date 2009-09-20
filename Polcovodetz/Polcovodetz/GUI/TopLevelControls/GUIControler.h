
#ifndef  __GUI_CONTROLLER__
#define  __GUI_CONTROLLER__

//-----------------------------------------------------------------

#include <Core/PObjects/PObject.h>

#include <QGraphicsScene>

#include <boost/shared_ptr.hpp>

//-----------------------------------------------------------------

struct GUIControlerImpl;

//-----------------------------------------------------------------
//ToDo: сделать отдельным АБСТРАКТНЫМ классом
class GUIControler : public QGraphicsScene
{
    Q_OBJECT;
public:
static const int SQUARE_SIZE = 32;

    GUIControler();

    virtual bool addObject( const PtrPObject& ); 

    virtual void updateMap();

public slots:
    virtual void updateObjects();
    virtual void deleteObject( const qint64 id );

private:
    boost::shared_ptr< GUIControlerImpl > m_impl;


};

//-----------------------------------------------------------------

#endif //__GUI_CONTROLLER__