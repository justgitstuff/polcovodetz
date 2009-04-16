
#ifndef __MAIN_FORM__
#define __MAIN_FORM__

//-----------------------------------------------------------------

#include <QMainWindow>
#include <boost/shared_ptr.hpp>

//-----------------------------------------------------------------

struct MainFormImpl;
struct LibDefinition;

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

    QFrame* getCommandTreeFrame( QWidget* parent );

private slots:
    void loadMap();

    void loadCommandController();

    void addLibraryToTable( const LibDefinition& );
};

//-----------------------------------------------------------------

#endif //__MAIN_FORM__

//-----------------------------------------------------------------

