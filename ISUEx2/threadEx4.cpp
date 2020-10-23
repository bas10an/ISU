#include "Vector.hpp"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
using namespace std;

struct DATA{
    Vector* vec;
    unsigned int ID; 
};

void *writerFunc(void *strukt){
    DATA* Data = (DATA*)strukt;
    while(1){
        if (!Data->vec->setAndTest(Data->ID)){      //if(not ***)
            cout << "Thread " << Data->ID << ": Error detected!" << endl;
        }
        sleep(1);
    }
    return NULL;
}

int main(){
    int amount = 0;
    cout << "Type amount of writers (default: 10): ";
    cin >> amount;
    amount = ((amount >= 1 && amount <= 100) ? amount : 10);
    cout << "Amount of writers set to: " << amount << endl;

    Vector vec;
    DATA Input[amount];
    pthread_t writer[amount];

    for(int i = 0; i < amount; i++){
        Input[i].ID = i;
        Input[i].vec = &vec;
        cout << "Creating thread with ID: " << i << endl;
        pthread_create(&writer[i], NULL, &writerFunc, &Input[i]);
    }
    while(1){}  //stay forever
    return 0;
}