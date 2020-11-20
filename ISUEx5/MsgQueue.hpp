#pragma once
#include "Message.hpp"
#include <iostream>
#include <queue>
using namespace std;

class MsgQueue
{
public:
    MsgQueue(unsigned long maxSize);
    void send(unsigned long id , Message* msg = NULL);
    Message* receive(unsigned long& id);
    ~MsgQueue();
private:
    // Container with messages
    queue<Message> *queue_;
    // Plus other relevant variables
    int maxSize_;
};

