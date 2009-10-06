#ifndef SCRIPTINVOKER_H
#define SCRIPTINVOKER_H

//-------------------------------------------------------

#include <QObject>

//-------------------------------------------------------

class ScriptInvoker : public QObject
{
    Q_OBJECT

public:
    ScriptInvoker();
    ~ScriptInvoker();

public slots:
    bool invokeScript( const QString& fileName );

private:
    
};

//-------------------------------------------------------

extern ScriptInvoker sInvoker;

//-------------------------------------------------------

#endif // SCRIPTINVOKER_H

//-------------------------------------------------------

