
#ifndef  __GUI_CONTROLLER__
#define  __GUI_CONTROLLER__

//-----------------------------------------------------------------

#include <Core/PObjects/PObject.h>

#include <QGraphicsScene>

#include <boost/shared_ptr.hpp>

//-----------------------------------------------------------------

struct GUIControlerImpl;

//-----------------------------------------------------------------
//ToDo: ������� ��������� ����������� �������
class GUIControler : public QGraphicsScene
{
    Q_OBJECT;
public:
static const int SQUARE_SIZE = 32;

    GUIControler();

    virtual bool addObject( const PtrPObject& ); 
    virtual bool deleteObject( const qint64 id );

    virtual void updateMap();

    virtual void updateObjects();

private:
    boost::shared_ptr< GUIControlerImpl > m_impl;


};

//-----------------------------------------------------------------

#endif //__GUI_CONTROLLER__