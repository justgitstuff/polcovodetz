﻿ 

#ifndef  __ICOMMAND_CONTROLLER
#define  __ICOMMAND_CONTROLLER

//-------------------------------------------------------

#include <IAbstractController.h>
#include <Messages.h>

//-------------------------------------------------------

class ICommandInputDriver;
class ICommandOutputDriver;

//-------------------------------------------------------
/**
  Интерфейс для "верховного главнокомандующего".
  Предполагаемые цели и задачи: принимать сообщения от 
  ядра ( PolkApp ) и подчиненных ( IGroupController ).

  Предполагается, что он должен решать, какие группы объектов
  куда направлять. 

  Гарантируется: класс работает асинхронно с ядром и с объектами других комманд.
  Приоритет потока не выше приоритета ядра.

  ToDo: сделать многопоточным.
  ToDo: определить таймаут инициализации.
*/
class ICommandController : public IAbstractController
{
    Q_OBJECT;

public:

    virtual ~ICommandController(){};

    /**
       Инициализация. Запускается ядром ДО начала игры.
       Из-за асинхронности класс может опаздать к началу игры, т. к. 
       долго конфигурировался.
    */
    virtual bool init( ICommandInputDriver*, ICommandOutputDriver* ) = 0;

public slots:
    virtual void message( CoreCommandMessage* ) = 0;
    virtual void message( GroupCommandMessage* ) = 0;
};

//-------------------------------------------------------

#endif //__ICOMMAND_CONTROLLER

//-------------------------------------------------------

