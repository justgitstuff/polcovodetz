
#ifndef __COMMAND_CONTROL_CHOOSE_FORM__
#define __COMMAND_CONTROL_CHOOSE_FORM__

//-----------------------------------------------------------------

#include <QDialog>
#include <boost/shared_ptr.hpp>

//-----------------------------------------------------------------

struct CommandControllerChooseFormImpl;

//-----------------------------------------------------------------

class CommandControllerChooseForm : public QDialog
{
    Q_OBJECT;
public:
    static int chooseCommandController( QWidget* parent = 0 );

private:
    CommandControllerChooseForm( QWidget* parent = 0 );

    boost::shared_ptr< CommandControllerChooseFormImpl > m_impl;

protected slots:
    void accept();
};

//-----------------------------------------------------------------

#endif //__COMMAND_CONTROL_CHOOSE_FORM__

//-----------------------------------------------------------------

