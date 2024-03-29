
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

    virtual void updateMap();

public slots:
    virtual void updateObjects();
    virtual void deleteObject( const qint64 id );
    virtual void addPObject( const PtrPObject& );

    virtual void addCrashMark( const QPoint& where );

private:
    boost::shared_ptr< GUIControlerImpl > m_impl;

    void updatePosition( const PtrPObject&, QGraphicsPixmapItem* );
};

//-----------------------------------------------------------------

#endif //__GUI_CONTROLLER__