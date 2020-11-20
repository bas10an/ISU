#include <pthread.h>
#include <unistd.h>
#include "Message.hpp"
#include "MsgQueue.hpp"
#include <iostream>
using namespace std;

pthread_mutex_t queueMut;
pthread_cond_t queueCond;

enum {ID_POINT_3D};
struct Point3D : public Message
{
    int x;
    int y;
    int z;
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
    MsgQueue* MSQ = (MsgQueue*)arg;
    while(1)
    {
        Message* p3D = MSQ->receive(handleMsg(ID_POINT_3D, static_cast<Point3D> msg));
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t S, R;
    pthread_mutex_init(&queueMut, NULL);
    pthread_cond_init(&queueCond, NULL);

    if(argc == 2)
    {
        MsgQueue MSQ(atoi(argv[1]));
        pthread_create(&S, NULL, Sender, &MSQ);
    }
    else
    {
        MsgQueue MSQ(1);
        pthread_create(&S, NULL, Sender, &MSQ);
    }
    while(1){}
    return 0;
}