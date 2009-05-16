
#ifndef __OBJECT_CONTROL_CHOOSE_FORM__
#define __OBJECT_CONTROL_CHOOSE_FORM__

//-----------------------------------------------------------------

#include <QDialog>
#include <boost/shared_ptr.hpp>

//-----------------------------------------------------------------

struct ObjectControllerChooseFormImpl;

//-----------------------------------------------------------------

class ObjectControllerChooseForm : public QDialog
{
    Q_OBJECT;
public:
    static int chooseObjectController( QWidget* parent = 0 );

private:
    ObjectControllerChooseForm( QWidget* parent = 0 );

    boost::shared_ptr< ObjectControllerChooseFormImpl > m_impl;

protected slots:
    void accept();
};

//-----------------------------------------------------------------

#endif //__OBJECT_CONTROL_CHOOSE_FORM__

//-----------------------------------------------------------------

