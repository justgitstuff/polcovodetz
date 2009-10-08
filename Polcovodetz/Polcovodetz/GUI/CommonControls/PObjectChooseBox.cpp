
//------------------------------------------------------------------------------

#include <GUI/CommonControls/PObjectChooseBox.h>

#include <Core/PObjectFactory.h>

#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QVector>

//------------------------------------------------------------------------------

struct PObjectChooseBoxImpl
{
    QTableWidget* tableWidget;

    QVector<int>  ids;
}; 

//------------------------------------------------------------------------------

PObjectChooseBox::PObjectChooseBox( QWidget* parent )
:QFrame( parent )
{
    m_impl.reset( new PObjectChooseBoxImpl() );

    QVBoxLayout* mainLayout    = new QVBoxLayout( this );

    m_impl->tableWidget        = new QTableWidget( this );

    mainLayout->addWidget( m_impl->tableWidget );

    m_impl->tableWidget->setColumnCount( 2 );

    m_impl->tableWidget->setHorizontalHeaderItem( 0, new QTableWidgetItem( tr( "Name" ) ) );
    m_impl->tableWidget->setHorizontalHeaderItem( 1, new QTableWidgetItem( tr( "Description" ) ) );

    int row = 0;

    const PObjectInfos& infos = pof.pObjectInfos();
    for( PObjectInfos::const_iterator iter = infos.constBegin();
        iter != infos.constEnd();
        iter++ )
    {
        if( iter->id < 1 )
            continue;

        m_impl->tableWidget->insertRow( row );

        m_impl->tableWidget->setItem( row, 0, new QTableWidgetItem( iter->name ) );
        m_impl->tableWidget->setItem( row, 1, new QTableWidgetItem( iter->description ) );

        m_impl->ids.append( iter->id );

        row++;
    }
}

//------------------------------------------------------------------------------

int PObjectChooseBox::PObjectID()const
{
    int row =  m_impl->tableWidget->currentRow();

    if( row < 0 )
        return -1;

    return m_impl->ids[ row ];
}

//------------------------------------------------------------------------------

void PObjectChooseBox::setPObjectID( const int id )
{
    for( int i = 0; i < m_impl->ids.count(); i++ )
    {
        if( m_impl->ids[ i ] == id )
        {
            m_impl->tableWidget->setCurrentCell( i, 0, QItemSelectionModel::Rows );
            return;
        }
    }
}

//------------------------------------------------------------------------------

