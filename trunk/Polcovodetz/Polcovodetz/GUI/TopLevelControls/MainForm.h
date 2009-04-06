
#ifndef __MAIN_FORM__
#define __MAIN_FORM__

//-----------------------------------------------------------------

#include <QtGUI/QMainWindow>
#include <boost/shared_ptr.hpp>

//-----------------------------------------------------------------

struct MainFormImpl;

class QFrame;

//-----------------------------------------------------------------

class MainForm : public QMainWindow
{
    Q_OBJECT;
public:
    MainForm();

protected:
    void virtual keyPressEvent( QKeyEvent* );

private:
    boost::shared_ptr< MainFormImpl > m_impl;

    QFrame* getOptionFrame( QWidget* parent );

    QFrame* getControllersFrame( QWidget* parent );

    QFrame* getRunTimeFrame( QWidget* parent );
    QFrame* getRunTimeOptionFrame( QWidget* parent );

private slots:
    void loadMap();

    void loadCommandController();
};

//-----------------------------------------------------------------

#endif //__MAIN_FORM__

//-----------------------------------------------------------------

