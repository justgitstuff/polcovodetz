﻿

#ifndef  __IABSTRACT_CONTROLLER
#define  __IABSTRACT_CONTROLLER

//-------------------------------------------------------

#include <QObject>
#include <QString>

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
class IAbstractController : public QObject
{
    Q_OBJECT;

public:
    virtual ~IAbstractController(){};

    /**Имя контролера*/
    virtual QString name()const                                         = 0;

    /**Краткое описание работы ( для отображения в таблице )*/
    virtual QString description()const                                  = 0;

    /**True, если собираемся обрабатывать нажатия клавиш*/
    virtual bool wantListenKeys()const{ return false; }

    /**Здесь можно реагировать на нажатия клавиш*/
    virtual void keyPressed( const Qt::Key ){ ; }
};

//-------------------------------------------------------

#endif //__IABSTRACT_CONTROLLER

//-------------------------------------------------------

