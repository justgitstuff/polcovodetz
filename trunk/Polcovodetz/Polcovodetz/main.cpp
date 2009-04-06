
//-------------------------------------------------------

#include <QtGui/QApplication>
#include <GUI/TopLevelControls/MainForm.h>
#include <QTranslator>

//-------------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );

    QTranslator translator;

    translator.load( "Russian" );/**Translate*/

    a.installTranslator( &translator );

    MainForm mainForm;

    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}

//-------------------------------------------------------

