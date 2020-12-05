#include "MsgQueue.hpp"

MsgQueue::MsgQueue(unsigned long maxSize)
: maxSize_(maxSize)
{
    pthread_mutex_init(&recMut, NULL);
    pthread_mutex_init(&sendMut, NULL);
    pthread_cond_init(&queueCond, NULL);
}


void MsgQueue::send(unsigned long id , Message* msg)
{
    pthread_mutex_lock(&sendMut);

    while(queue_.size() == maxSize_)
    {
        pthread_cond_wait(&queueCond, &sendMut);
    }
    queue_.push({id, msg});

    pthread_cond_broadcast(&queueCond); //queue not empty

    pthread_mutex_unlock(&sendMut);
}


Message* MsgQueue::receive(unsigned long& id)
{
    pthread_mutex_lock(&recMut);

    while(queue_.size() == 0)
    {
        pthread_cond_wait(&queueCond, &recMut);
    }
    id = queue_.front().first;
    Message* msg = queue_.front().second;
    queue_.pop();

    pthread_cond_broadcast(&queueCond); //queue not full
    pthread_mutex_unlock(&recMut);

    return msg;
}


MsgQueue::~MsgQueue()
{
    pthread_mutex_destroy(&recMut);
    pthread_mutex_destroy(&sendMut);
    pthread_cond_destroy(&queueCond);
}