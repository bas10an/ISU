#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

struct Input{
    unsigned int ID;
};

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
    Input *DATA = (Input*)arg;
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
    cout << "Car #" << DATA->ID << " entered parkinglot." << endl;
    int time = 1 + (rand() % 10);
    sleep(time);

    /*.. Exit ..*/
    pthread_mutex_lock(&m);
    carWaiting = true;
    pthread_cond_signal(&Exit);

    while(!PLCS_EXIT_IS_OPEN)
        pthread_cond_wait(&Exit, &m);

    carWaiting = false;
    pthread_cond_signal(&Exit);
    pthread_mutex_unlock(&m);
    cout << "Car #" << DATA->ID << " exited parkinglot" << endl;
    return NULL;
}

int main(int argc, char* argv[]){
    srand((unsigned) time(0));
    pthread_mutex_init(&m,NULL);

    int num = atoi(argv[1]);

    pthread_t car[num];
    pthread_t PLCS_entry_door;
    pthread_t PLCS_exit_door;

    Input Data[num];

    pthread_create(&PLCS_entry_door, NULL, PLCS_entry, NULL);
    pthread_create(&PLCS_exit_door, NULL, PLCS_exit, NULL);
    
    for(int i = 0; i<=num; i++){
        Data[i].ID = i;
        pthread_create(&car[i], NULL, CAR, &Data[i]);
    }

    while(1){}

    return 0;
}