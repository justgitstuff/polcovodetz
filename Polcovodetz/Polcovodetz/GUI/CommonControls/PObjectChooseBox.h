
#ifndef __POBJECT_CHOOSE_BOX__
#define __POBJECT_CHOOSE_BOX__

//-----------------------------------------------------------------

#include <QFrame>
#include <QPair>
#include <boost/shared_ptr.hpp>

//-----------------------------------------------------------------

struct PObjectChooseBoxImpl;


//-----------------------------------------------------------------

class PObjectChooseBox : public QFrame
{
    Q_OBJECT;
public:
    PObjectChooseBox( QWidget* parent = 0 );

    int  PObjectID()const;
    void setPObjectID( const int id );

private:
    boost::shared_ptr< PObjectChooseBoxImpl > m_impl;

};

//-----------------------------------------------------------------

#endif //__POBJECT_CHOOSE_BOX__

//-----------------------------------------------------------------

