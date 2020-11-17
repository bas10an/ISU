#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

struct Input{
    unsigned int ID;
};

pthread_mutex_t mEntry, mExit;
pthread_cond_t entry, Exit;

bool PLCS_ENTRY_IS_OPEN = false;
bool PLCS_EXIT_IS_OPEN = false;
bool carWaiting = false;

/*....................................PLCS_Entry....................................*/
void* PLCS_entry(void* arg){
    while(1){
    pthread_mutex_lock(&mEntry);

    while(!carWaiting)
        pthread_cond_wait(&entry, &mEntry);

    PLCS_ENTRY_IS_OPEN = true;
    cout << "Entry Opened." << endl;
    pthread_cond_signal(&entry);
    while(carWaiting)
        pthread_cond_wait(&entry, &mEntry);
    
    PLCS_ENTRY_IS_OPEN = false;
    cout << "Entry Closed." << endl;
    pthread_mutex_unlock(&mEntry);
    }
    return NULL;
}

/*....................................PLCS_Exit....................................*/
void* PLCS_exit(void* arg){
    while(1){
    pthread_mutex_lock(&mExit);
    
    while(!carWaiting)
        pthread_cond_wait(&Exit, &mExit);

    PLCS_EXIT_IS_OPEN = true;
    cout << "Exit Opened." << endl;
    pthread_cond_signal(&Exit);
    while(carWaiting)
        pthread_cond_wait(&Exit, &mExit);
    
    PLCS_EXIT_IS_OPEN = false;
    cout << "Exit Closed." << endl;
    pthread_mutex_unlock(&mExit);
    }
    return NULL;
}

/*....................................CAR....................................*/
void* CAR(void* arg){
    Input *DATA = (Input*)arg;
    /*....Car Entry....*/
    pthread_mutex_lock(&mEntry);
    carWaiting = true;
    pthread_cond_signal(&entry);

    while(!PLCS_ENTRY_IS_OPEN)
        pthread_cond_wait(&entry, &mEntry);

    carWaiting = false;
    pthread_cond_signal(&entry);
    pthread_mutex_unlock(&mEntry);

    /*....Entered and waiting before Exiting....*/
    cout << "Car #" << DATA->ID << " entered parkinglot." << endl;
    int time = 1 + (rand() % 5);
    cout << "Parking for " << time << " seconds." << endl;
    sleep(time);

    /*....Car Exit....*/
    pthread_mutex_lock(&mExit);
    carWaiting = true;
    pthread_cond_signal(&Exit);

    while(!PLCS_EXIT_IS_OPEN)
        pthread_cond_wait(&Exit, &mExit);

    carWaiting = false;
    pthread_cond_signal(&Exit);
    pthread_mutex_unlock(&mExit);
    cout << "Car #" << DATA->ID << " exited parkinglot" << endl;
    return NULL;
}

/*....................................Main....................................*/
int main(int argc, char* argv[]){
    srand((unsigned) time(0));
    pthread_mutex_init(&mEntry,NULL);
    pthread_mutex_init(&mExit,NULL);
    pthread_cond_init(&entry, NULL);
    pthread_cond_init(&Exit, NULL);

    int num = atoi(argv[1]);

    pthread_t car[num];
    pthread_t PLCS_entry_door;
    pthread_t PLCS_exit_door;

    Input Data[num];

    pthread_create(&PLCS_entry_door, NULL, PLCS_entry, NULL);
    pthread_create(&PLCS_exit_door, NULL, PLCS_exit, NULL);
    
    for(int i = 0; i<num; i++){
        Data[i].ID = i;
        pthread_create(&car[i], NULL, CAR, &Data[i]);
    }

    while(1){}

    return 0;
}