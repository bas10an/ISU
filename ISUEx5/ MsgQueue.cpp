#include "MsgQueue.hpp"
#include "main.cpp"

MsgQueue::MsgQueue(unsigned long maxSize)
: maxSize_(maxSize), queue_(new queue<Message>)
{
}

void MsgQueue::send(unsigned long id , Message* msg = NULL)
{
    if(queue_->size() >= maxSize_)
    {
        pthread_mutex_lock(&queueMut);
        while(queue_->size() >= maxSize_)
        {
            pthread_cond_wait(&queueCond, &queueMut);
        }
        pthread_mutex_unlock(&queueMut);
    }
}

Message* MsgQueue::receive(unsigned long& id)
{
    if(queue_->size() <= 0)
    {
        pthread_mutex_lock(&queueMut);
        while(queue_->size() <= 0)
        {
            pthread_cond_wait(&queueCond, &queueMut);
        }
        pthread_mutex_unlock(&queueMut);
    }
}

MsgQueue::~MsgQueue()
{
    delete queue_;
}