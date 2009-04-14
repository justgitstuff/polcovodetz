
//------------------------------------------------------------------------------

#include <GUI/TopLevelControls/CommandTreeForm.h>

#include <Core/PolkApp.h>
#include <GUI/CommonControls/CommandControllerChooseForm.h>
#include <GUI/CommonControls/GroupControllerChooseForm.h>

#include <QAction>
#include <QMessageBox>
#include <QSplitter>
#include <QTreeWidget>
#include <QToolBar>
#include <QVBoxLayout>

//------------------------------------------------------------------------------

struct CommandTreeFormImpl
{
    QTreeWidget*                  treeWidget1;
    QTreeWidget*                  treeWidget2;

    QAction*                      loadCommandController1;
    QAction*                      loadCommandController2;

    QAction*                      loadGroupController1;
    QAction*                      loadGroupController2;

    QMap< QTreeWidgetItem*, int > ids;
};

//------------------------------------------------------------------------------

CommandTreeForm::CommandTreeForm( QWidget* parent )
:QFrame( parent )
{
    m_impl.reset( new CommandTreeFormImpl() );

    QToolBar* toolBar = new QToolBar( tr( "Properties" ), this );

    m_impl->loadCommandController1 = new QAction( this );
    m_impl->loadCommandController2 = new QAction( this );

    QVBoxLayout* mainLayout        = new QVBoxLayout( this );

    QSplitter* mainSplitter        = new QSplitter( Qt::Horizontal, this );

    m_impl->treeWidget1            = createTree( mainSplitter );
    m_impl->treeWidget2            = createTree( mainSplitter );

    mainLayout->addWidget( toolBar );
    mainLayout->addWidget( mainSplitter );

    //actions
    m_impl->loadCommandController1 = toolBar->addAction( tr( "LoadCommandController1" ), this, SLOT( loadCommandController1() ) );
    m_impl->loadCommandController2 = toolBar->addAction( tr( "LoadCommandController2" ), this, SLOT( loadCommandController2() ) );

    m_impl->loadGroupController1 = toolBar->addAction( tr( "LoadGroupController1" ), this, SLOT( loadGroupController1() ) );
    m_impl->loadGroupController2 = toolBar->addAction( tr( "LoadGroupController2" ), this, SLOT( loadGroupController2() ) );
}

//------------------------------------------------------------------------------

QTreeWidget* CommandTreeForm::createTree( QWidget* parent )
{
    QTreeWidget* tw = new QTreeWidget( parent );

    tw->setHeaderLabels( QStringList( tr( "Name" ) ) );

    return tw;
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

    int id = -2 + side;

    QTreeWidget* tw = side == 1 ? m_impl->treeWidget1 : m_impl->treeWidget2;

    QTreeWidgetItem* newItem = new QTreeWidgetItem( tw, QStringList( pApp.library( libID ).ccName ) );

    m_impl->ids.insert( newItem, id );
}

//------------------------------------------------------------------------------

void CommandTreeForm::loadGroupController1()
{
    return loadGroupController( 1 );
}

//------------------------------------------------------------------------------

void CommandTreeForm::loadGroupController2()
{
    return loadGroupController( 2 );
}

//------------------------------------------------------------------------------

void CommandTreeForm::loadGroupController( const int side )
{
    int libID = CommandControllerChooseForm::chooseCommandController( this );

    if( libID < 1 )
        return;
    
    if ( !pApp.registerGroupController( libID, side ) )
    {
        QMessageBox::warning( this, tr( "Error" ), tr( "ErrorDuringRegistrationCommandController" ) );

        return;
    }

    int id = -2 + side;

    QTreeWidget* tw = side == 1 ? m_impl->treeWidget1 : m_impl->treeWidget2;

    QTreeWidgetItem* newItem = new QTreeWidgetItem( tw, QStringList( pApp.library( libID ).gcName ) );

    m_impl->ids.insert( newItem, id );
}

//------------------------------------------------------------------------------

