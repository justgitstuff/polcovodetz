

#ifndef  __ILOADER
#define  __ILOADER

//-------------------------------------------------------

#include <QString>

class ICommandController;
class IGroupController;
class IObjectController;

//-------------------------------------------------------
/**
    Класс - загрузчик различный контроллеров.

    ToDo: встроить адекватную систему интернационализации
*/
class ILoader
{
public:

    virtual QString             name()const           = 0;
    virtual QString             description()const    = 0;

    virtual                     ~ILoader(){};
 
    /**
        Выдает новый экземпляр ICommandController.
        Возможнен вызов PolkApp `ом более часто, нежели требуется, 
        для проведение тестовых замеров.
    */
    virtual ICommandController* getCommandController() = 0;

    /**
        Выдает новый экземпляр IGroupController.
        Возможнен вызов PolkApp `ом более часто, нежели требуется, 
        для проведение тестовых замеров.
    */

    virtual IGroupController*   getGroupController()   = 0;
    /**
        Выдает новый экземпляр IObjectController.
        Возможнен вызов PolkApp `ом более часто, нежели требуется, 
        для проведение тестовых замеров.
    */
    virtual IObjectController*  getObjectController()  = 0;
};

//-------------------------------------------------------

#endif //__ILOADER

//-------------------------------------------------------

