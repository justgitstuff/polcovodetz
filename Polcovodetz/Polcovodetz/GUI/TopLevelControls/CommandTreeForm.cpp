
//------------------------------------------------------------------------------

#include <GUI/TopLevelControls/CommandTreeForm.h>

#include <Core/PolkApp.h>
#include <GUI/CommonControls/CommandControllerChooseForm.h>

#include <QAction>
#include <QMessageBox>
#include <QSplitter>
#include <QTreeWidget>
#include <QToolBar>
#include <QVBoxLayout>

//------------------------------------------------------------------------------

struct CommandTreeFormImpl
{
    QTreeWidget* treeWidget1;
    QTreeWidget* treeWidget2;

    QAction*     loadCommandController1;
    QAction*     loadCommandController2;
};

//------------------------------------------------------------------------------

CommandTreeForm::CommandTreeForm( QWidget* parent )
:QFrame( parent )
{
    m_impl.reset( new CommandTreeFormImpl() );

    QToolBar* toolBar = new QToolBar( tr( "Properties" ), this );

    m_impl->loadCommandController1 = new QAction( this );
    m_impl->loadCommandController2 = new QAction( this );

    QVBoxLayout* mainLayout = new QVBoxLayout( this );

    QSplitter* mainSplitter = new QSplitter( Qt::Horizontal, this );

    m_impl->treeWidget1      = new QTreeWidget( mainSplitter );
    m_impl->treeWidget2      = new QTreeWidget( mainSplitter );

    mainLayout->addWidget( toolBar );
    mainLayout->addWidget( mainSplitter );

    //actions

    m_impl->loadCommandController1 = toolBar->addAction( tr( "LoadCommandController1" ), this, SLOT( loadCommandController1() ) );
    m_impl->loadCommandController2 = toolBar->addAction( tr( "LoadCommandController2" ), this, SLOT( loadCommandController2() ) );
}

//------------------------------------------------------------------------------

void CommandTreeForm::loadCommandController1()
{
    return loadCommandController( 1 );
}

//------------------------------------------------------------------------------

void CommandTreeForm::loadCommandController2()
{
    return loadCommandController( 2 );
}

//------------------------------------------------------------------------------

void CommandTreeForm::loadCommandController( const int side )
{
    int libID = CommandControllerChooseForm::chooseCommandController( this );

    if( libID < 1 )
        return;

    if ( !pApp.registerCommandController( libID, side ) )
    {
        QMessageBox::warning( this, tr( "Error" ), tr( "ErrorDuringRegistrationCommandController" ) );

        return;
    }

    /* добавление в дерево */
}

//------------------------------------------------------------------------------

