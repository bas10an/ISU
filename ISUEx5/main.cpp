#include "Message.hpp"
#include "MsgQueue.hpp"
#include <unistd.h>
using namespace std;

pthread_mutex_t printMutex;

#define LOG(...) do { \
    pthread_mutex_lock(&printMutex); \
    std::cout << "[" << __FILE__ << ":" << __LINE__ << "] (" << __FUNCTION__ << ") :" \
    << __VA_ARGS__;  \
    pthread_mutex_unlock(&printMutex); \
} while(0)


enum
{
    POINT3D_IND
};


struct Point3D : public Message
{
    int x, y, z;
};


void* Sender(void* arg)
{
    MsgQueue* mq = (MsgQueue*)arg;
    for(unsigned long i = 0;; i++)
    {
        Point3D* point3D = new Point3D;
        point3D->x = i;
        point3D->y = i;
        point3D->z = i;
        mq->send(POINT3D_IND, point3D);
        sleep(1);
    }
    return NULL;
}


void printPoint3DVars(Point3D* P3D)
{
    LOG("Point 3D - x: " << P3D->x << " y: " << P3D->y << " z: " << P3D->y << endl);
}


void handleMsg(unsigned int id, Message* msg)
{
    switch(id)
    {
        case POINT3D_IND:
            printPoint3DVars(static_cast<Point3D*>(msg));
    }
}

void* Receiver(void* arg)
{
    MsgQueue* mq = (MsgQueue*)arg;
    unsigned long id;
    while(1)
    {
        Message* msg = mq->receive(id);
        handleMsg(id, msg);
        delete msg;
    }
    return NULL;
}


int main(int argc, char* argv[])
{
    pthread_t S, R;
    unsigned long MQSIZE = atoi(argv[1]);

    MsgQueue* mq = argc >= 2 ? new MsgQueue(MQSIZE) : new MsgQueue(1);

    pthread_create(&S, NULL, Sender, &mq);
    pthread_create(&R, NULL, Receiver, &mq);
    
    while(1){}
    return 0;
}