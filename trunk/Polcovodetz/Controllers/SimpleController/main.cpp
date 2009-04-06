
//-------------------------------------------------------

#include <Implementations/Loader.h>

//-------------------------------------------------------

#ifdef Q_WS_WIN
    #define MY_EXPORT __declspec(dllexport)
#else
    #define MY_EXPORT
#endif

//-------------------------------------------------------

extern "C" MY_EXPORT ILoader* getLoader()
{
    return new Loader();
}

//-------------------------------------------------------

