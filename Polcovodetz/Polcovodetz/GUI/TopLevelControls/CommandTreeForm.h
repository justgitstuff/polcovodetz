
#ifndef __COMMAND_TREE_FORM__
#define __COMMAND_TREE_FORM__

//-----------------------------------------------------------------

#include <QFrame>
#include <boost/shared_ptr.hpp>

//-----------------------------------------------------------------

struct CommandTreeFormImpl;

class QTreeWidget;
class QTreeWidgetItem;

//-----------------------------------------------------------------

class CommandTreeForm : public QFrame
{
    Q_OBJECT;
public:
    CommandTreeForm( QWidget* parent = 0 );

private:
    boost::shared_ptr< CommandTreeFormImpl > m_impl;

    void loadCommandController( const int side );
    void loadGroupController( const int side );
    void loadObjectController( const int side );

    QTreeWidget* createTree( QWidget* parent );

    void itemSelected( QTreeWidgetItem* item, const int side );

    void disableAllActions();

private slots:
    void loadCommandController1();
    void loadCommandController2();

    void loadGroupController1();
    void loadGroupController2();

    void loadObjectController1();
    void loadObjectController2();

    void command1ItemSelected( QTreeWidgetItem* item );
    void command2ItemSelected( QTreeWidgetItem* item );
};

//-----------------------------------------------------------------

#endif //__COMMAND_TREE_FORM__

//-----------------------------------------------------------------

