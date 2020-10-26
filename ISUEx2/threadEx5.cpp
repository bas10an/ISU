#include "Vector.hpp"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
using namespace std;
//For checking time
#include <time.h>

struct DATA{
    Vector* vec;
    unsigned int ID; 
    unsigned int interval;
};

void *writerFunc(void *strukt){
    DATA* Data = (DATA*)strukt;
    const clock_t begin_time = clock();     //timer start
    int ti = 0;
    while(1){
        if (!Data->vec->setAndTest(Data->ID)){      //if(not ***)
            cout << "Thread " << Data->ID << ": Error detected!" << endl;
            if(ti == 0){
                cout << "Thread " << Data->ID << " detected an error after: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " s" << endl;       //timer print
                ti = 1;
            }
        }
        usleep((Data->interval)*1000);
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

    int interval2 = 0;
    cout << "Type loop timein ms(default: 1000ms): ";
    cin >> interval2;
    interval2 = ((interval2 >= 1 && interval2 <= 1000) ? interval2 : 1000);
    cout << "Loop time set to: " << interval2 << "ms" << endl;

    for(int i = 0; i < amount; i++){
        Input[i].ID = i;
        Input[i].vec = &vec;
        Input[i].interval = interval2;
        cout << "Creating thread with ID: " << i << endl;
        pthread_create(&writer[i], NULL, &writerFunc, &Input[i]);
    }
    while(1){}  //stay forever
    return 0;
}