
#ifndef __COMMAND_TREE_FORM__
#define __COMMAND_TREE_FORM__

//-----------------------------------------------------------------

#include <QFrame>
#include <boost/shared_ptr.hpp>

//-----------------------------------------------------------------

struct CommandTreeFormImpl;

//-----------------------------------------------------------------

class CommandTreeForm : public QFrame
{
    Q_OBJECT;
public:
    CommandTreeForm( QWidget* parent = 0 );

private:
    boost::shared_ptr< CommandTreeFormImpl > m_impl;

private slots:
};

//-----------------------------------------------------------------

#endif //__COMMAND_TREE_FORM__

//-----------------------------------------------------------------

