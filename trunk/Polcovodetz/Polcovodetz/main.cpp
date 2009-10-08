
//-------------------------------------------------------

#include <GUI/TopLevelControls/MainForm.h>

#include <QApplication>
#include <QLocale>
#include <QTranslator>

//-------------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );

    QLocale::setDefault( QLocale( QLocale::Russian, QLocale::RussianFederation ) );

    QTranslator translator;

    /**Translate*/
    if( !translator.load( "Russian" ) )
        translator.load( "English" );

    a.installTranslator( &translator );

    MainForm mainForm;

    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}

//-------------------------------------------------------

