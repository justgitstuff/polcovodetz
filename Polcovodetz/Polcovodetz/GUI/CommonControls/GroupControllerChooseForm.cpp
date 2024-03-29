
//------------------------------------------------------------------------------

#include <GUI/CommonControls/GroupControllerChooseForm.h>

#include <Core/PolkApp.h>
#include <Core/LibraryLoader.h>

#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QVector>

//------------------------------------------------------------------------------

struct GroupControllerChooseFormImpl
{
    QTableWidget* tableWidget;

    QVector<int>  ids;

    int           curentId;
}; 

//------------------------------------------------------------------------------

GroupControllerChooseForm::GroupControllerChooseForm( QWidget* parent )
:QDialog( parent )
{
    m_impl.reset( new GroupControllerChooseFormImpl() );

    QVBoxLayout* mainLayout    = new QVBoxLayout( this );

    m_impl->tableWidget        = new QTableWidget( this );

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    
    QPushButton* bOk           = new QPushButton( tr( "Ok" ),     this );
    QPushButton* bCancel       = new QPushButton( tr( "Cancel" ), this );

    mainLayout->addWidget( m_impl->tableWidget );
    mainLayout->addLayout( buttonsLayout );

    buttonsLayout->addStretch();
    buttonsLayout->addWidget( bOk );
    buttonsLayout->addWidget( bCancel );

    connect( bOk,     SIGNAL( clicked( bool ) ), this, SLOT( accept() ) );
    connect( bCancel, SIGNAL( clicked( bool ) ), this, SLOT( reject() ) );

    m_impl->tableWidget->setColumnCount( 2 );

    m_impl->tableWidget->setHorizontalHeaderItem( 0, new QTableWidgetItem( tr( "Name" ) ) );
    m_impl->tableWidget->setHorizontalHeaderItem( 1, new QTableWidgetItem( tr( "Description" ) ) );

    LibraryLoader::LibDefinitions defs = libLoader.loadedLibraries();

    int row = 0;

    for( LibraryLoader::LibDefinitions::ConstIterator iter = defs.constBegin();
        iter != defs.constEnd();
        iter++
        )
    {
        if( iter->gcName.isEmpty() )
            continue;

        m_impl->tableWidget->insertRow( row );

        m_impl->tableWidget->setItem( row, 0, new QTableWidgetItem( iter->gcName ) );
        m_impl->tableWidget->setItem( row, 1, new QTableWidgetItem( iter->gcDescription ) );

        m_impl->ids.append( iter->id );

        row++;
    }
}

//------------------------------------------------------------------------------

void GroupControllerChooseForm::accept()
{
    QList< QTableWidgetItem* > items = m_impl->tableWidget->selectedItems();

    if( items.isEmpty() )
    {
        m_impl->curentId = 0;
        return;
    }

    QTableWidgetItem* first = items.first();

    int row = first->row();

    m_impl->curentId = m_impl->ids[ row ];

    QDialog::accept();
}

//------------------------------------------------------------------------------

int GroupControllerChooseForm::chooseGroupController( QWidget* parent )
{
    GroupControllerChooseForm form( parent );

    form.exec();

    return form.m_impl->curentId;
}

//------------------------------------------------------------------------------

