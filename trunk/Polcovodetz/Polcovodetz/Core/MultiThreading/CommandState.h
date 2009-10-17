
#ifndef  __COMMAND_STATE__
#define  __COMMAND_STATE__

//-------------------------------------------------------

#include <QObject>

#include <boost/shared_ptr.hpp>

#include <Core/PObjects/PObject.h>

//-------------------------------------------------------

struct CommandStateImpl;
class CoreCommandMessage;
class CoreObjectMessage;
class AbstractMessage;
class DriverHelper;

//-------------------------------------------------------

typedef QVector< int > IDEnumeration;

//-------------------------------------------------------

namespace
{
	/**
		Перечисление, обозначающее, кому направлено сообщение
	*/
    enum MsgElement
    {
        None, 
		Core, 
		CommandController, 
		GroupController, 
		ObjectController
    };

	/**
		Некоторое действие, которое может добавиться в очередь для выполнения.
	*/
    struct Action
    {
        MsgElement                           who;
        MsgElement                           toWhom;
        boost::shared_ptr< AbstractMessage > message;        

        Action():toWhom( None ), who( None ), message(){};

    };

    typedef boost::shared_ptr< Action > ActionPtr;
}

//-------------------------------------------------------
/**
	
	Класс, занимающийся менеджментом комманды.
	Также контролирует очереди сообщений
*/
class CommandState : public QObject
{
    Q_OBJECT;
public:
    /**
		Конструктор, создает класс по параметру side.
		side может быть только 1 или 2.
	*/
    CommandState( const int side );


    /**
		Сторона комманды ( 1 или 2 )
	*/
	int                 side()const;

	/**
		Регистрирует контроллер комманды. Выдает true, если все прошло успешно, иначе false.
	*/
    bool                registerCommandController( const int libraryID );
    /**
		Регистрирует контроллер группы. Вызвращает id при успешном завершении
	*/
    int                 registerGroupController( const int libraryID );
    /**
		Регистрирует контроллер объекта. Возвращает id при успешном завершении.
	*/
    int                 registerObjectController( const int libraryID, const int gID, const int pObject );

    /**
		Id контроллера комманды
	*/
    int                 commandController();
    /**
		Список id от контроллерова групп	
	*/
    IDEnumeration       groupControllers();
    /**
		Список id от контроллеров объектов в группе с groupID
	*/
    IDEnumeration       objectControllers( const int groupID );

    /**
		ID библиотеки контроллера комманды
	*/
    int                 commandControllerLibId();
    /**
		ID библиотеки для контроллера группы
	*/
    int                 groupControllerLibId( const int groupID );
    /**
		ID библиотеки для контроллера объекта
	*/
    int                 objectControllerLibId( const int objectID );
    /**
		ID для объекта
	*/
    int                 objectControllerPObject( const int objectID );

    /**
		Отправка сообщения ( сообщение ставится в очередь и обрабатывается уже в коммандном потоке )
	*/
    int                 sendMessage( boost::shared_ptr< AbstractMessage > message );

    /**
		Установить скорость объекта
	*/
    bool                setSpeed( const PtrPObject&, const QPoint& persent );
    /**
		Устанавливает поворот объекта.
	*/
    bool                setRotation( const PtrPObject&, int angle );
     
    /**
		Создает объект и присоединяет его к списку активных объектов.
	*/
    void                createConnectedObject( const int rtti, const qint64 driverID );

    /**
		Создает ракету, прикрепляя её к объекту
	*/
    void                makeRocket( const PtrPObject& who );

    /**
		Функция прикрепляет драйверы к объектам. 
		Используется PolkApp`ом при старте игры
	*/
    bool                connectDrivers();
    /**
		Запускает процесс обработки сообщений
	*/
    void                sendInnerMessages( const int maxMessages = 100 );

    /**
		Выдает структуру DriveHelper - специальный модуль для операций с драйверами. 
		Ускореят выполение запросов из-за ассимптотики.
	*/
    DriverHelper*       driverHelper()const;

public slots:
    void                disposeObject( const qint64 id );    
    void                updatePositions( bool sendSignals = true );

private:

    boost::shared_ptr< CommandStateImpl > m_impl;
};

//-------------------------------------------------------

#endif //__COMMAND_STATE__