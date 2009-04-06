
//------------------------------------------------------------------------------

#include <GUI/TopLevelControls/MainForm.h>
#include <GUI/SpecialControls/PaintArea2D.h>

#include <Core/PolkApp.h>

#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QTabWidget>
#include <QTranslator>
#include <QFrame>
#include <QKeyEvent>
#include <QPushButton>
#include <QSplitter>
#include <QTableWidget>
#include <QVBoxLayout>

//------------------------------------------------------------------------------

struct MainFormImpl
{
    QPushButton*  startButton;
    QPushButton*  pauseButton;

    QPushButton*  loadCommandControllerButton;

    QTableWidget* libraryTable;
};

//------------------------------------------------------------------------------

MainForm::MainForm()
:QMainWindow()
{
    m_impl.reset( new MainFormImpl() );

    show();

    setWindowTitle( tr( "Polcovodetz" ) );

    QTabWidget* mainTabWidget = new QTabWidget( this );

    mainTabWidget->addTab( getOptionFrame( mainTabWidget ),       tr( "Options" ) );
    mainTabWidget->addTab( getControllersFrame( mainTabWidget ),  tr( "ControllersOptions" ) );
    mainTabWidget->addTab( getRunTimeFrame( mainTabWidget ),      tr( "GamePane" ) );

    setCentralWidget( mainTabWidget );

   // QKeyEvent* k = new QKeyEvent( QEvent::Type::
    return;
}

//------------------------------------------------------------------------------

QFrame* MainForm::getOptionFrame( QWidget* parent )
{
    QFrame* frame             = new QFrame( parent );
    QGridLayout* mainLayout   = new QGridLayout( frame );

    QGroupBox* mapBox         = new QGroupBox( frame ); 
    QVBoxLayout* mapBoxLayout = new QVBoxLayout( mapBox );

    QPushButton* loadMap      = new QPushButton( tr( "LoadMap" ), mapBox );

    connect( loadMap, SIGNAL( clicked() ), this, SLOT( loadMap() ) );

    mapBoxLayout->addWidget( loadMap );
    mainLayout->addWidget( mapBox, 0, 0 );

    return frame;
}

//------------------------------------------------------------------------------

QFrame* MainForm::getRunTimeFrame( QWidget* parent )
{
    QFrame*      frame        = new QFrame( parent );
    QHBoxLayout* mainLayout   = new QHBoxLayout( frame );

    QFrame*      leftPanel    = getRunTimeOptionFrame( frame );

    mainLayout->addWidget( leftPanel );
    mainLayout->addWidget( pApp.currentView() );

    return frame;
}

//------------------------------------------------------------------------------

QFrame* MainForm::getRunTimeOptionFrame( QWidget* parent )
{
    QFrame*      frame                = new QFrame( parent );
    QVBoxLayout* mainLayout           = new QVBoxLayout( frame );
    
    QGroupBox*   stateBox             = new QGroupBox( frame ); 
    QVBoxLayout* stateBoxLayout       = new QVBoxLayout( stateBox );

                 m_impl->startButton  = new QPushButton( tr( "StartGame" ), stateBox );
                 m_impl->pauseButton  = new QPushButton( tr( "PauseGame" ), stateBox );

    connect( m_impl->startButton, SIGNAL( clicked() ), &pApp, SLOT( startGame() ) );

    stateBoxLayout->addWidget( m_impl->startButton );
    stateBoxLayout->addWidget( m_impl->pauseButton );

    mainLayout->addWidget( stateBox );

    return frame;
}

//------------------------------------------------------------------------------

QFrame* MainForm::getControllersFrame( QWidget* parent )
{
    QSplitter*   splitter             = new QSplitter( parent );

    QFrame*      leftFrame            = new QFrame( splitter );
    QVBoxLayout* buttonsLayout        = new QVBoxLayout( leftFrame );

                 m_impl->loadCommandControllerButton 
                     = new QPushButton( tr( "LoadCommandController" ), leftFrame );

                 m_impl->libraryTable = new QTableWidget( 0, 2, splitter );

    connect( m_impl->loadCommandControllerButton, SIGNAL( clicked() ), this, SLOT( loadCommandController() ) );

    m_impl->libraryTable->setHorizontalHeaderItem( 0, new QTableWidgetItem( tr( "LibraryName" ) ) );
    m_impl->libraryTable->setHorizontalHeaderItem( 1, new QTableWidgetItem( tr( "LibraryDescription" ) ) );

    m_impl->libraryTable->setColumnWidth( 0, 100 );
    m_impl->libraryTable->setColumnWidth( 1, 200 );

    buttonsLayout->addWidget( m_impl->loadCommandControllerButton );
    buttonsLayout->addWidget( pApp.loadInfoView() );

    return splitter;
}

//------------------------------------------------------------------------------

void MainForm::keyPressEvent( QKeyEvent* event )
{
    switch( event->key() )
    {
    case Qt::Key_Return :
        {
            if ( event->modifiers() & Qt::ALT )
            {
                if( isFullScreen() )
                    showNormal();
                else
                    showFullScreen();
            }
            break;
        }
    default:
        return QMainWindow::keyPressEvent( event );
    }
    
}

//------------------------------------------------------------------------------

void MainForm::loadMap()
{
    QString fileName = QFileDialog::getOpenFileName( 
                this, tr( "OpenMapFile" ), 
                QDir::current().absolutePath(), 
                tr( "MapFiles *.pmap" ) 
            ); 

    if( !fileName.isEmpty() )
    {
        if ( !pApp.reloadMap( fileName ) )
        {
            QMessageBox::critical( this, tr( "LoadingError" ), tr( "ErrorDuringLoadMapFile" ) );
        }        
    }
}

//------------------------------------------------------------------------------

void MainForm::loadCommandController()
{
    QString fileName = QFileDialog::getOpenFileName( 
                this, tr( "NativeControllerFile" ), 
                QDir::current().absolutePath(), 
                tr( "All files *.*" ) 
            ); 

    if( !fileName.isEmpty() )
    {
        if ( !pApp.loadLibrary( fileName ) )
        {
            QMessageBox::critical( this, tr( "LoadingError" ), tr( "ErrorDuringLoadNativeControllerFile" ) );
        }        
    }
}

//------------------------------------------------------------------------------

