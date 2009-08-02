
//------------------------------------------------------------------------------

#include <GUI/TopLevelControls/MainForm.h>

#include <GUI/TopLevelControls/CommandTreeForm.h>
#include <GUI/SpecialControls/PaintArea2D.h>

#include <Core/PolkApp.h>
#include <Core/LibraryLoader.h>

#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QFileDialog>
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
    QPushButton*     startButton;
    QPushButton*     pauseButton;

    QPushButton*     loadCommandControllerButton;

    QTableWidget*    libraryTable;
    QTableWidget*    controllerTable;

    CommandTreeForm* commandTree;
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
    mainTabWidget->addTab( getCommandTreeFrame( mainTabWidget ),  tr( "CommandTree" ) );

    setCentralWidget( mainTabWidget );

    mainTabWidget->setMovable( true );

    connect( &libLoader, SIGNAL( newLibrary( const LibDefinition& ) ), this, SLOT( addLibraryToTable( const LibDefinition& ) ) );
    return;
}

//------------------------------------------------------------------------------

QFrame* MainForm::getOptionFrame( QWidget* parent )
{
    QFrame*      frame           = new QFrame( parent );
    QVBoxLayout* mainLayout      = new QVBoxLayout( frame );

    QGroupBox*   mapBox          = new QGroupBox( frame ); 
    QVBoxLayout* mapBoxLayout    = new QVBoxLayout( mapBox );

    QPushButton* loadMap         = new QPushButton( tr( "LoadMap" ), mapBox );

    QGroupBox*   scriptBox       = new QGroupBox( frame ); 
    QVBoxLayout* scriptBoxLayout = new QVBoxLayout( scriptBox );

    QPushButton* loadScript        = new QPushButton( tr( "InvokeScript" ), scriptBox );

    connect( loadMap,    SIGNAL( clicked() ), this, SLOT( loadMap() ) );
    connect( loadScript, SIGNAL( clicked() ), this, SLOT( invokeScript() ) );

    mapBoxLayout->addWidget( loadMap );

    scriptBoxLayout->addWidget( loadScript );

    mainLayout->addWidget( mapBox );
    mainLayout->addWidget( scriptBox );
    mainLayout->addStretch();

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
    QSplitter*   splitter                = new QSplitter( parent );

    QFrame*      leftFrame               = new QFrame( splitter );
    QSplitter*   tableSplitter           = new QSplitter( Qt::Vertical, splitter );

    QVBoxLayout* buttonsLayout           = new QVBoxLayout( leftFrame );

                 m_impl->loadCommandControllerButton 
                     = new QPushButton( tr( "LoadControlLibrary" ), leftFrame );

                 m_impl->libraryTable    = new QTableWidget( 0, 2, tableSplitter );
                 m_impl->controllerTable = new QTableWidget( 0, 3, tableSplitter );

    connect( m_impl->loadCommandControllerButton, SIGNAL( clicked() ), this, SLOT( loadCommandController() ) );

    m_impl->libraryTable->setHorizontalHeaderItem( 0, new QTableWidgetItem( tr( "LibraryName" ) ) );
    m_impl->libraryTable->setHorizontalHeaderItem( 1, new QTableWidgetItem( tr( "LibraryDescription" ) ) );

    m_impl->libraryTable->setColumnWidth( 0, 100 );
    m_impl->libraryTable->setColumnWidth( 1, 200 );

    m_impl->controllerTable->setHorizontalHeaderItem( 0, new QTableWidgetItem( tr( "ControllerType" ) ) );
    m_impl->controllerTable->setHorizontalHeaderItem( 1, new QTableWidgetItem( tr( "ControllerName" ) ) );
    m_impl->controllerTable->setHorizontalHeaderItem( 2, new QTableWidgetItem( tr( "ControllerDescription" ) ) );

    m_impl->libraryTable->setSortingEnabled( true );
    m_impl->controllerTable->setSortingEnabled( true );

    buttonsLayout->addWidget( m_impl->loadCommandControllerButton );
    buttonsLayout->addWidget( libLoader.loadInfoView() );

    return splitter;
}

//------------------------------------------------------------------------------

QFrame* MainForm::getCommandTreeFrame( QWidget* parent )
{
    m_impl->commandTree = new CommandTreeForm( parent );

    return m_impl->commandTree;
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
        if ( !libLoader.loadLibrary( fileName ) )
        {
            QMessageBox::critical( this, tr( "LoadingError" ), tr( "ErrorDuringLoadNativeControllerFile" ) );
        }        
    }
}

//------------------------------------------------------------------------------

void MainForm::addLibraryToTable( const LibDefinition& lib )
{
    try
    {
        m_impl->libraryTable->setSortingEnabled( false );
        m_impl->controllerTable->setSortingEnabled( false );

        int row = m_impl->libraryTable->rowCount();
        m_impl->libraryTable->insertRow( row );

        m_impl->libraryTable->setItem( row, 0, new QTableWidgetItem( lib.name ) );
        m_impl->libraryTable->setItem( row, 1, new QTableWidgetItem( lib.descritpion ) );

        if( !lib.ccName.isEmpty() )
        {
            int row = m_impl->controllerTable->rowCount();
            m_impl->controllerTable->insertRow( row );

            m_impl->controllerTable->setItem( row, 0, new QTableWidgetItem( tr( "CommandController" ) ) );
            m_impl->controllerTable->setItem( row, 1, new QTableWidgetItem( lib.ccName ) );
            m_impl->controllerTable->setItem( row, 2, new QTableWidgetItem( lib.ccDescription ) );
        }

        if( !lib.gcName.isEmpty() )
        {
            int row = m_impl->controllerTable->rowCount();
            m_impl->controllerTable->insertRow( row );

            m_impl->controllerTable->setItem( row, 0, new QTableWidgetItem( tr( "GroupController" ) ) );
            m_impl->controllerTable->setItem( row, 1, new QTableWidgetItem( lib.gcName ) );
            m_impl->controllerTable->setItem( row, 2, new QTableWidgetItem( lib.gcDescription ) );
        }

        if( !lib.ocName.isEmpty() )
        {
            int row = m_impl->controllerTable->rowCount();
            m_impl->controllerTable->insertRow( row );

            m_impl->controllerTable->setItem( row, 0, new QTableWidgetItem( tr( "ObjectController" ) ) );
            m_impl->controllerTable->setItem( row, 1, new QTableWidgetItem( lib.ocName ) );
            m_impl->controllerTable->setItem( row, 2, new QTableWidgetItem( lib.ocDescription ) );
        }
    }
    catch( ... )
    {
        qDebug( "Error during updating controllers at the controller table" );
    }
    
    m_impl->libraryTable->setSortingEnabled( true );
    m_impl->controllerTable->setSortingEnabled( true );

}

//------------------------------------------------------------------------------

void MainForm::invokeScript()
{
    QString str = QFileDialog::getOpenFileName( this, tr( "ScriptInvoking" ), QString::null, tr( "ScriptFiles | *.script" ) );

    if( str.isEmpty() )
        return;

    if( !pApp.invokeScript( str ) )
        QMessageBox::warning( this, tr( "ScriptInvoking" ), tr( "ThereAreErrorsDuringInvokingScript" ) );
}

//------------------------------------------------------------------------------

