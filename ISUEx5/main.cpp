#include <pthread.h>
#include <unistd.h>
#include "Message.hpp"
#include "MsgQueue.hpp"
#include <iostream>
using namespace std;

pthread_mutex_t queueMut;
pthread_cond_t queueCond;

enum
{
    ID_POINT_3D
};

struct Point3D : public Message
{
    int x;
    int y;
    int z;
};

struct Item
{
    Message* msg_;
    MsgQueue* mq_;
};

void* Sender(void* arg)
{
    MsgQueue* MSQ = (MsgQueue*)arg;
    while(1)
    {
        MSQ->send(ID_POINT_3D, new Point3D);
    }
    sleep(1);
    return NULL;
}

void handleMsg(unsigned int id, Message* msg)
{
    switch(id)
    {
        case ID_POINT_3D:
            
    }
}

void* Receiver(void* arg)
{
    Item* ITEM = (Item*)arg;
    while(1)
    {
        Message* p3D = ITEM->mq_->receive(handleMsg(ID_POINT_3D, ITEM->msg_));
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t S, R;
    pthread_mutex_init(&queueMut, NULL);
    pthread_cond_init(&queueCond, NULL);

    Item item;
    item.mq_ = argc >= 2 ? new MsgQueue(atoi(argv[1])) : new MsgQueue(1);
    item.id = 1;

    pthread_create(&S, NULL, Sender, &item);
    pthread_create(&R, NULL, Receiver, &item);
    
    while(1){}
    return 0;
}