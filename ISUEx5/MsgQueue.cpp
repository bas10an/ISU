#include "MsgQueue.hpp"

pthread_mutex_t queueMut;
pthread_cond_t queueCond;

MsgQueue::MsgQueue(unsigned long maxSize)
: maxSize_(maxSize), queue_(new queue<pair<unsigned long, Message*>>)
{
    pthread_mutex_init(&queueMut, NULL);
    pthread_cond_init(&queueCond, NULL);
}

void MsgQueue::send(unsigned long id , Message* msg)
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
    pair <unsigned long, Message*> pair_;
    pair_.first = id;
    pair_.second = msg;
    queue_->push(pair_);
    pthread_cond_signal(&queueCond); //qq
}

Message* MsgQueue::receive(unsigned long& id)
{
    Message* msg;

    if(queue_->size() <= 0)
    {
        pthread_mutex_lock(&queueMut);
        while(queue_->size() <= 0)
        {
            pthread_cond_wait(&queueCond, &queueMut);
        }
        pthread_mutex_unlock(&queueMut);
    }
    pair <unsigned long, Message*> msgPair = queue_->front();
    
    id = queue_->front().first;
    msg = queue_->front().second;
    queue_->pop();
    pthread_cond_signal(&queueCond); //queue not full

    return msg;
}

MsgQueue::~MsgQueue()
{
    delete queue_;
}