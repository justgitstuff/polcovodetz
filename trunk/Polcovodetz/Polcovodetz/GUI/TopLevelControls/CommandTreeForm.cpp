//------------------------------------------------------------------------------

#include <GUI/TopLevelControls/CommandTreeForm.h>

#include <Core/LibraryLoader.h>
#include <Core/PObjectFactory.h>
#include <Core/PolkApp.h>
#include <Core/ResourceManager.h>

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
    CommandTreeFormImpl( CommandTreeForm* form )
        :cController1( 0 ), cController2( 0 ), treeWidget1( 0 ), treeWidget2( 0 ),
        currentItem( 0 ), parent( form )

    { }
    CommandTreeForm*              parent;
    QTreeWidgetItem*              currentItem;

    QToolBar*                     toolBar;

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

    QAction*                      refreshAll;

    QMap< QTreeWidgetItem*, int > ids;

    QAction* getAction( const ResourceManager::Picturies, const QString& name , const char* member );
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

QAction* CommandTreeFormImpl::getAction( const ResourceManager::Picturies pict, 
                                        const QString& name , 
                                        const char* member )
{
    return toolBar->addAction( resMan.image( pict ), name, parent, member );
}

//------------------------------------------------------------------------------

CommandTreeForm::CommandTreeForm( QWidget* parent )
:QFrame( parent )
{
    m_impl.reset( new CommandTreeFormImpl( this ) );

    m_impl->toolBar                = new QToolBar( tr( "Properties" ), this );

    QVBoxLayout* mainLayout        = new QVBoxLayout( this );

    QSplitter* mainSplitter        = new QSplitter( Qt::Horizontal, this );

    m_impl->treeWidget1            = createTree( mainSplitter );
    m_impl->treeWidget2            = createTree( mainSplitter );

    mainLayout->addWidget( m_impl->toolBar );
    mainLayout->addWidget( mainSplitter );    

    //actions
    m_impl->loadCommandController1 = m_impl->getAction( ResourceManager::Command, tr( "LoadCommandController1" ), SLOT( loadCommandController1() ) );
    m_impl->loadCommandController2 = m_impl->getAction( ResourceManager::Command, tr( "LoadCommandController2" ), SLOT( loadCommandController2() ) );

    m_impl->loadGroupController1   = m_impl->getAction( ResourceManager::Group, tr( "LoadGroupController1" ), SLOT( loadGroupController1() ) );
    m_impl->loadGroupController2   = m_impl->getAction( ResourceManager::Group, tr( "LoadGroupController2" ), SLOT( loadGroupController2() ) );

    m_impl->loadObjectController1  = m_impl->getAction( ResourceManager::Object,tr( "LoadObjectController1" ), SLOT( loadObjectController1() ) );
    m_impl->loadObjectController2  = m_impl->getAction( ResourceManager::Object,tr( "LoadObjectController2" ), SLOT( loadObjectController2() ) );

    m_impl->refreshAll             = m_impl->getAction( ResourceManager::Refresh,tr( "Refresh" ), SLOT( refresh() ) );

    m_impl->treeWidget1->setContextMenuPolicy( Qt::ActionsContextMenu );
    m_impl->treeWidget2->setContextMenuPolicy( Qt::ActionsContextMenu );

    m_impl->treeWidget1->addAction( m_impl->loadCommandController1 );
    m_impl->treeWidget2->addAction( m_impl->loadCommandController2 );

    m_impl->treeWidget1->addAction( m_impl->loadGroupController1 );
    m_impl->treeWidget2->addAction( m_impl->loadGroupController2 );

    m_impl->treeWidget1->addAction( m_impl->loadObjectController1 );
    m_impl->treeWidget2->addAction( m_impl->loadObjectController2 );

    disableAllActions();

    //connections
    connect( m_impl->treeWidget1, SIGNAL( currentItemChanged( QTreeWidgetItem*, QTreeWidgetItem* ) ), this, SLOT( command1ItemSelected( QTreeWidgetItem* ) ) );
    connect( m_impl->treeWidget2, SIGNAL( currentItemChanged( QTreeWidgetItem*, QTreeWidgetItem* ) ), this, SLOT( command2ItemSelected( QTreeWidgetItem* ) ) );
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

    cc = new QTreeWidgetItem( tw, QStringList( libLoader.library( libID ).ccName ) );

    m_impl->ids.insert( cc, id );

    if( side == 1 )
        m_impl->cController1 = cc;
    else
        m_impl->cController2 = cc;

    cc->setSelected( true );
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
    GroupItem* group = dynamic_cast< GroupItem* >( m_impl->currentItem );
    if( !group )
    {
        QMessageBox::warning( this, tr( "Error" ), tr( "CantLoadObjectController:cantUnderstand:ToWhichGroupShouldAttachController" ) );

        return;
    }

    QPair< int, int > libID = ObjectControllerChooseForm::chooseObjectController( this );

    if( libID.first < 1 || libID.second < 1 )
        return;

    int id = pApp.registerObjectController( libID.first, side, group->id(), libID.second );
    
    if ( id < 1 )
    {
        QMessageBox::warning( this, tr( "Error" ), tr( "ErrorDuringRegistrationObjectController" ) );

        return;
    }

    QTreeWidgetItem* newItem = new ObjectItem( 
        group, 
        libLoader.library( libID.first ).ocName + tr( " ON " ) + pof.pObjectInfo( libID.second ).name, id );

    m_impl->ids.insert( newItem, id );

    disableAllActions();
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

    QTreeWidgetItem* newItem = new GroupItem( twi, libLoader.library( libID ).gcName, id );

    m_impl->ids.insert( newItem, id );

    disableAllActions();
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

    m_impl->refreshAll->setEnabled( true );
}

//------------------------------------------------------------------------------

void CommandTreeForm::itemSelected( QTreeWidgetItem* item, const int side )
{
    disableAllActions();

    m_impl->currentItem = item;

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

void CommandTreeForm::refresh()
{
    m_impl->treeWidget1->clear();
    m_impl->treeWidget2->clear();

    m_impl->ids.clear();

    m_impl->cController1 = 0;
    m_impl->cController2 = 0;

    int cc1 = pApp.commandController( 1 );

    if( cc1 != 0 )
    {
        m_impl->cController1 = new QTreeWidgetItem( m_impl->treeWidget1, QStringList( libLoader.library( pApp.commandControllerLibId( 1 ) ).ccName ) );

        IDEnumeration groups = pApp.groupControllers( 1 );
        for( IDEnumeration::const_iterator iter = groups.constBegin();
             iter != groups.constEnd();
             iter++ )
        {            
            int id = *iter;

            int libId = pApp.groupControllerLibId( 1, id );

            GroupItem* group = new GroupItem( m_impl->cController1, libLoader.library( libId ).gcName, id );

            m_impl->ids.insert( group, id );

            IDEnumeration objects = pApp.objectControllers( 1, id );

            for( IDEnumeration::const_iterator iter = objects.constBegin();
                 iter != objects.constEnd();
                 iter++ )
            {            
                int id = *iter;

                int libId = pApp.objectControllerLibId( 1, id );

                new ObjectItem( group, libLoader.library( libId ).ocName + tr( " ON " ) + pof.pObjectInfo( pApp.objectControllerPObject( 1, id ) ).name, id );
            }
        }
    }

    int cc2 = pApp.commandController( 2 );

    if( cc2 != 0 )
    {
        m_impl->cController2 = new QTreeWidgetItem( m_impl->treeWidget2, QStringList( libLoader.library( pApp.commandControllerLibId( 2 ) ).ccName ) );

        IDEnumeration groups = pApp.groupControllers( 2 );
        for( IDEnumeration::const_iterator iter = groups.constBegin();
             iter != groups.constEnd();
             iter++ )
        {            
            int id = *iter;

            int libId = pApp.groupControllerLibId( 2, id );

            GroupItem* group = new GroupItem( m_impl->cController2, libLoader.library( libId ).gcName, id );

            m_impl->ids.insert( group, id );

            IDEnumeration objects = pApp.objectControllers( 2, id );

            for( IDEnumeration::const_iterator iter = objects.constBegin();
                 iter != objects.constEnd();
                 iter++ )
            {            
                int id = *iter;

                int libId = pApp.objectControllerLibId( 2, id );

                new ObjectItem( group, libLoader.library( libId ).ocName + tr( " ON " ) + pof.pObjectInfo( pApp.objectControllerPObject( 2, id ) ).name, id );
            }
        }
    }

    m_impl->treeWidget1->expandAll();
    m_impl->treeWidget2->expandAll();
}

//------------------------------------------------------------------------------
