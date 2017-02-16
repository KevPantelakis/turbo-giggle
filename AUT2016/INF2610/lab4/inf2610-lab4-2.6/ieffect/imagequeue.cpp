#include <QImage>
#include <QDebug>
#include <QQueue>

#include "imagequeue.h"
#include "simpletracer.h"

ImageQueue::ImageQueue(QObject *parent, int capacity) :
    QObject(parent),
    m_capacity(capacity)
{
    handleQ = CreateSemaphore(NULL, capacity, capacity, NULL);
    handleDQ = CreateSemaphore(NULL, 0, capacity, NULL);    
}

ImageQueue::~ImageQueue()
{

}
// Lorsque la file est vide, alors le consommateur bloque et attend qu'un élément soit produit.
// Lorsque la file est pleine, alors le producteur bloque et attend qu'un élément soit libéré.
void ImageQueue::enqueue(QImage *item)
{
    WaitForSingleObject(handleQ, INFINITE);
    // tracer la taille de la file lorsqu'elle change
    SimpleTracer::writeEvent(this, 0);
    queue.enqueue(item);
    ReleaseSemaphore(handleDQ, 1, NULL);
}

QImage *ImageQueue::dequeue()
{
    WaitForSingleObject(handleDQ, INFINITE);
    // tracer la taille de la file lorsqu'elle change
    SimpleTracer::writeEvent(this, 0);
    ReleaseSemaphore(handleQ, 1, NULL);
    return queue.dequeue();
}
