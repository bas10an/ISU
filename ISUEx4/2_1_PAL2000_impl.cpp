#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

pthread_mutex_t m;
pthread_cond_t entry;
pthread_cond_t Exit;

bool PLCS_ENTRY_IS_OPEN = false;
bool PLCS_EXIT_IS_OPEN = false;
bool carWaiting = false;

void* PLCS_entry(void* arg){
    while(1){
    pthread_mutex_lock(&m);

    while(!carWaiting)
        pthread_cond_wait(&entry, &m);

    PLCS_ENTRY_IS_OPEN = true;
    cout << "Entry Opened." << endl;
    pthread_cond_signal(&entry);
    while(carWaiting)
        pthread_cond_wait(&entry, &m);
    
    PLCS_ENTRY_IS_OPEN = false;
    cout << "Entry Closed." << endl;
    pthread_mutex_unlock(&m);
    }
    return NULL;
}

void* PLCS_exit(void* arg){
    while(1){
    pthread_mutex_lock(&m);
    
    while(!carWaiting)
        pthread_cond_wait(&Exit, &m);

    PLCS_EXIT_IS_OPEN = true;
    cout << "Exit Opened." << endl;
    pthread_cond_signal(&Exit);
    while(carWaiting)
        pthread_cond_wait(&Exit, &m);
    
    PLCS_EXIT_IS_OPEN = false;
    cout << "Exit Closed." << endl;
    pthread_mutex_unlock(&m);
    }
    return NULL;
}

void* CAR(void* arg){
    /*.. Entry ..*/
    pthread_mutex_lock(&m);
    carWaiting = true;
    pthread_cond_signal(&entry);

    while(!PLCS_ENTRY_IS_OPEN)
        pthread_cond_wait(&entry, &m);

    carWaiting = false;
    pthread_cond_signal(&entry);
    pthread_mutex_unlock(&m);

    /*.. Entered and waiting before Exiting ..*/
    cout << "Car entered parkinglot." << endl;
    sleep(2);

    /*.. Exit ..*/
    pthread_mutex_lock(&m);
    carWaiting = true;
    pthread_cond_signal(&Exit);

    while(!PLCS_EXIT_IS_OPEN)
        pthread_cond_wait(&Exit, &m);

    carWaiting = false;
    pthread_cond_signal(&Exit);
    pthread_mutex_unlock(&m);
    cout << "Car exited parkinglot." << endl;
    return NULL;
}

int main(){
    pthread_mutex_init(&m,NULL);

    pthread_t car;
    pthread_t PLCS_entry_door;
    pthread_t PLCS_exit_door;

    pthread_create(&PLCS_entry_door, NULL, PLCS_entry, NULL);
    pthread_create(&PLCS_exit_door, NULL, PLCS_exit, NULL);
    pthread_create(&car, NULL, CAR, NULL);

    while(1){}

    return 0;
}