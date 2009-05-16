
//------------------------------------------------------------------------------

#include <GUI/TopLevelControls/CommandTreeForm.h>

#include <Core/PolkApp.h>
#include <GUI/CommonControls/CommandControllerChooseForm.h>
#include <GUI/CommonControls/GroupControllerChooseForm.h>
#include <GUI/CommonControls/ObjectControllerChooseForm.h>

#include <QAction>
#include <QMessageBox>
#include <QSplitter>
#include <QTreeWidget>
#include <QToolBar>
#include <QVBoxLayout>

//------------------------------------------------------------------------------

struct CommandTreeFormImpl
{
    CommandTreeFormImpl()
        :cController1( 0 ), cController2( 0 ), treeWidget1( 0 ), treeWidget2( 0 )
    { }

    QTreeWidget*                  treeWidget1;
    QTreeWidget*                  treeWidget2;

    QTreeWidgetItem*              cController1;
    QTreeWidgetItem*              cController2;

    QAction*                      loadCommandController1;
    QAction*                      loadCommandController2;

    QAction*                      loadGroupController1;
    QAction*                      loadGroupController2;

    QAction*                      loadObjectController1;
    QAction*                      loadObjectController2;

    QMap< QTreeWidgetItem*, int > ids;
};

//------------------------------------------------------------------------------

class GroupItem : public QTreeWidgetItem
{
public:
    GroupItem( QTreeWidgetItem* command, const QString& name, const int id )
        :QTreeWidgetItem( command, QStringList( name ) ), m_id( id ){ }

    int id()const{ return m_id; }

private:
    int m_id;
};

//------------------------------------------------------------------------------

class ObjectItem : public QTreeWidgetItem
{
public:
    ObjectItem( GroupItem* command, const QString& name, const int id )
        :QTreeWidgetItem( command, QStringList( name ) ), m_id( id ){ }

    int id()const{ return m_id; }

private:
    int m_id;
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

    m_impl->loadObjectController1 = toolBar->addAction( tr( "LoadObjectController1" ), this, SLOT( loadObjectController1() ) );
    m_impl->loadObjectController2 = toolBar->addAction( tr( "LoadObjectController2" ), this, SLOT( loadObjectController2() ) );

    disableAllActions();

    //connections
    connect( m_impl->treeWidget1, SIGNAL( itemChanged( QTreeWidgetItem* , int ) ), this, SLOT( command1ItemSelected( QTreeWidgetItem* ) ) );
    connect( m_impl->treeWidget2, SIGNAL( itemChanged( QTreeWidgetItem* , int ) ), this, SLOT( command2ItemSelected( QTreeWidgetItem* ) ) );
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
    QTreeWidgetItem* cc = ( side == 1 ? m_impl->cController1 : m_impl->cController2 );

    if( cc != 0 )
    {
        QMessageBox::warning( this, tr( "Error" ), tr( "ControllerHasAlreadyAdded" ) );

        return;
    }

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

    cc = new QTreeWidgetItem( tw, QStringList( pApp.library( libID ).ccName ) );

    m_impl->ids.insert( cc, id );

    if( side == 1 )
        m_impl->cController1 = cc;
    else
        m_impl->cController2 = cc;
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

void CommandTreeForm::loadObjectController1()
{
    return loadObjectController( 1 );
}

//------------------------------------------------------------------------------

void CommandTreeForm::loadObjectController2()
{
    return loadObjectController( 2 );
}

//------------------------------------------------------------------------------

void CommandTreeForm::command1ItemSelected( QTreeWidgetItem* item )
{
    itemSelected( item, 1 );
}

//------------------------------------------------------------------------------

void CommandTreeForm::command2ItemSelected( QTreeWidgetItem* item )
{
    itemSelected( item, 2 );
}

//------------------------------------------------------------------------------

void CommandTreeForm::loadObjectController( const int side )
{
    if( !m_impl->cController1 )
    {
        QMessageBox::warning( this, tr( "Error" ), tr( "CantLoadGroupControllerBeforeLoadingCommandsController" ) );

        return;
    }

    int libID = ObjectControllerChooseForm::chooseObjectController( this );

    if( libID < 1 )
        return;

    int id = pApp.registerObjectController( libID, 0, side, 0 );
    
    if ( id < 1 )
    {
        QMessageBox::warning( this, tr( "Error" ), tr( "ErrorDuringRegistrationObjectController" ) );

        return;
    }
/*
    QTreeWidgetItem* twi = side == 1 ? m_impl->cController1 : m_impl->cController2;

    QTreeWidgetItem* newItem = new GroupItem( twi, pApp.library( libID ).gcName, id );

    m_impl->ids.insert( newItem, id );*/
}
//------------------------------------------------------------------------------

void CommandTreeForm::loadGroupController( const int side )
{
    if( !m_impl->cController1 )
    {
        QMessageBox::warning( this, tr( "Error" ), tr( "CantLoadGroupControllerBeforeLoadingCommandsController" ) );

        return;
    }

    int libID = GroupControllerChooseForm::chooseGroupController( this );

    if( libID < 1 )
        return;

    int id = pApp.registerGroupController( libID, side );
    
    if ( id < 1 )
    {
        QMessageBox::warning( this, tr( "Error" ), tr( "ErrorDuringRegistrationGroupController" ) );

        return;
    }

    QTreeWidgetItem* twi = side == 1 ? m_impl->cController1 : m_impl->cController2;

    QTreeWidgetItem* newItem = new GroupItem( twi, pApp.library( libID ).gcName, id );

    m_impl->ids.insert( newItem, id );
}

//------------------------------------------------------------------------------

void CommandTreeForm::disableAllActions()
{
    m_impl->loadCommandController1->setEnabled( !m_impl->cController1 );
    m_impl->loadCommandController2->setEnabled( !m_impl->cController2 );

    m_impl->loadGroupController1->setEnabled( false );
    m_impl->loadGroupController2->setEnabled( false );

    m_impl->loadObjectController1->setEnabled( false );
    m_impl->loadObjectController2->setEnabled( false );
}

//------------------------------------------------------------------------------

void CommandTreeForm::itemSelected( QTreeWidgetItem* item, const int side )
{
    disableAllActions();

    if( item == m_impl->cController1 )
    {
        m_impl->loadGroupController1->setEnabled( true );
        return;
    }
    if( item == m_impl->cController2 )
    {
        m_impl->loadGroupController2->setEnabled( true );
        return;
    }

    if( dynamic_cast< GroupItem* >( item ) )
    {
        m_impl->loadObjectController1->setEnabled( side == 1 );
        m_impl->loadObjectController2->setEnabled( side == 2 );
    }
}

//------------------------------------------------------------------------------
