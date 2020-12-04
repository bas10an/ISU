#pragma once
#include "Message.hpp"
#include <iostream>
#include <queue>
#include <pthread.h>
using namespace std;

class MsgQueue
{
public:
    MsgQueue(unsigned long maxSize);
    void send(unsigned long id , Message* msg);
    Message* receive(unsigned long& id);
    ~MsgQueue();
private:
    // Container with messages
    queue<pair<unsigned long, Message*>>* queue_;
    // Plus other relevant variables
    int maxSize_;
};
