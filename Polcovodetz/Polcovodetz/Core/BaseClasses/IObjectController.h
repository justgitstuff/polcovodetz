﻿

#ifndef  __IOBJECT_CONTROLLER
#define  __IOBJECT_CONTROLLER

//-------------------------------------------------------

#include <IAbstractController.h>
#include <Messages.h>

//-------------------------------------------------------

class IObjectInputDriver;
class IObjectOutputDriver;

//-------------------------------------------------------
/**
  Интерфейс для "коммаднира объекта".
  Предполагаемые цели и задачи: принимать сообщения от 
  "командира группы" ( IGroupController ) и, через дрйвер, изменять скорости/ускорение,
  стрелять.

  Предполагается, что он должен решать, как направлять один объект на базе комманд свыше.

  Гарантируется: класс работает асинхронно с ядром и с объектами других комманд.
  Приоритет потока не выше приоритета ядра.

  ToDo: сделать многопоточным.
  ToDo: определить таймаут инициализации.
*/
class IObjectController : public IAbstractController
{
    Q_OBJECT;

public:    

    /**Инициализация. Запускается ядром ДО начала игры.
       Из-за асинхронности класс может опаздать к началу игры, т. к. 
       долго конфигурировался.
    */
    virtual bool    init( IObjectInputDriver*, IObjectOutputDriver* ) = 0;

signals:
    void sendTopMessage( ObjectGroupMessage* );
    //void sendDownMessage( GroupObjectMessage* );
};

//-------------------------------------------------------

#endif //__IOBJECT_CONTROLLER

//-------------------------------------------------------

