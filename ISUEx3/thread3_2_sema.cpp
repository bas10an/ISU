#include "Vector.hpp"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
using namespace std;
//For checking time
#include <time.h>
#include <semaphore.h>

struct DATA{
    Vector* vec;
    unsigned int ID; 
};

sem_t s1;

void *writerFunc(void *strukt){
    DATA* Data = (DATA*)strukt;
    const clock_t begin_time = clock();     //timer start
    int ti = 0;
    while(1){
        sem_wait(&s1);
        if (!Data->vec->setAndTest(Data->ID)){      //if(not ***)
            cout << "Thread " << Data->ID << ": Error detected!" << endl;
            //print time for error
            if(ti == 0){
                cout << "Thread " << Data->ID << " detected an error after: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " s" << endl;       //timer print
                ti = 1;
            }
        }
        cout << "Thread #" << Data->ID << " done." << endl;
        sem_post(&s1);
        sleep(1);
    }
    return NULL;
}

int main(){
    if(sem_init(&s1,0,1) != 0) 
    {
        cout << "Semaphore init Error!" << endl;
        return -1;
    }

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
    sem_destroy(&s1);

    return 0;
}