
#ifndef  __ABSTRACT_MESSAGE
#define  __ABSTRACT_MESSAGE

//-------------------------------------------------------

#include <QVariant>

//-------------------------------------------------------
/**
 Базовый класс сообщения.

 Основные принципы:
 1) Очередь комманды МОЖЕТ ОСТАНОВИТЬСЯ при выполнении сообщения. 
 2) Драйвер ОБЯЗАН НЕМЕДЛЕННО запустить соответствующие функции у "подчиненного" в том же потоке.

*/
class AbstractMessage
{
public:
    AbstractMessage( qint64 id = -1 ):m_id( id ){};

    void setInfo( const QVariant& );
    QVariant info()const;

    qint64 id()const{ return m_id; }

    virtual int rtti()const = 0;

    static const int RTTI = 0;

private:
    qint64 m_id;
};

//-------------------------------------------------------

#endif //__ABSTRACT_MESSAGE

//-------------------------------------------------------

