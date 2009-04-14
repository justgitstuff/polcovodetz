
#ifndef __GROUP_CONTROL_CHOOSE_FORM__
#define __GROUP_CONTROL_CHOOSE_FORM__

//-----------------------------------------------------------------

#include <QDialog>
#include <boost/shared_ptr.hpp>

//-----------------------------------------------------------------

struct GroupControllerChooseFormImpl;

//-----------------------------------------------------------------

class GroupControllerChooseForm : public QDialog
{
    Q_OBJECT;
public:
    static int chooseGroupController( QWidget* parent = 0 );

private:
    GroupControllerChooseForm( QWidget* parent = 0 );

    boost::shared_ptr< GroupControllerChooseFormImpl > m_impl;

protected slots:
    void accept();
};

//-----------------------------------------------------------------

#endif //__GROUP_CONTROL_CHOOSE_FORM__

//-----------------------------------------------------------------

