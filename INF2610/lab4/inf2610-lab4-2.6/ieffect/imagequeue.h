#ifndef IMAGEQUEUE_H
#define IMAGEQUEUE_H

#include <windows.h>
#include <QObject>
#include <QQueue>

class QImage;

class ImageQueue : public QObject
{
    Q_OBJECT
public:
    explicit ImageQueue(QObject *parent = 0, int capacity = 4);
    ~ImageQueue();
    void enqueue(QImage *item);
    QImage *dequeue();
    bool isEmpty();
private:
    int m_capacity;
    QQueue<QImage*> queue;
    HANDLE handleQ;
    HANDLE handleDQ;
};

#endif // IMAGEQUEUE_H
