#ifndef CRASHIMAGEITEM_H
#define CRASHIMAGEITEM_H

//-------------------------------------------------------------

#include <QGraphicsPixmapItem>

#include <boost/shared_ptr.hpp>

//-------------------------------------------------------------

struct CrashImageItemImpl;

//-------------------------------------------------------------

class CrashImageItem : public QGraphicsPixmapItem
{

public:
    CrashImageItem();
    ~CrashImageItem();

    void nextStep();

private:
    boost::shared_ptr < CrashImageItemImpl > m_impl;
};

//-------------------------------------------------------------

#endif // CRASHIMAGEITEM_H

//-------------------------------------------------------------

