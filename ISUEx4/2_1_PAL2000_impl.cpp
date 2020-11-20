#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

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

    cout << "PLCS Entry - Opened." << endl;
    PLCS_ENTRY_IS_OPEN = true;

    pthread_cond_signal(&entry);
    while(carWaiting)
        pthread_cond_wait(&entry, &mEntry);
    
    cout << "PLCS Entry - Closed." << endl;
    PLCS_ENTRY_IS_OPEN = false;

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

    cout << "PLCS Exit - Opened." << endl;
    PLCS_EXIT_IS_OPEN = true;
    
    pthread_cond_signal(&Exit);
    while(carWaiting)
        pthread_cond_wait(&Exit, &mExit);
    
    cout << "PLCS Exit - Closed." << endl;
    PLCS_EXIT_IS_OPEN = false;
    
    pthread_mutex_unlock(&mExit);
    }
    return NULL;
}

/*....................................CAR....................................*/
void* CAR(void* arg){
    while(1){
        /*....Car Entry....*/
        pthread_mutex_lock(&mEntry);
        cout << "CAR - Waiting at Entry." << endl;
        carWaiting = true;
        pthread_cond_signal(&entry);

        while(!PLCS_ENTRY_IS_OPEN)
            pthread_cond_wait(&entry, &mEntry);

        carWaiting = false;
        pthread_cond_signal(&entry);
        cout << "CAR - Enters parkinglot." << endl;
        pthread_mutex_unlock(&mEntry);

        /*....Entered and waiting before Exiting....*/
        
        int time = 2;
        cout << "CAR - Parking for " << time << " seconds." << endl;
        sleep(time);

        /*....Car Exit....*/
        pthread_mutex_lock(&mExit);
        carWaiting = true;
        pthread_cond_signal(&Exit);

        while(!PLCS_EXIT_IS_OPEN)
            pthread_cond_wait(&Exit, &mExit);

        carWaiting = false;
        pthread_cond_signal(&Exit);
        cout << "CAR - Exits parkinglot" << endl;
        pthread_mutex_unlock(&mExit);

        sleep(time);
    }
    return NULL;
}

/*....................................Main....................................*/
int main(){
    pthread_mutex_init(&mEntry,NULL);
    pthread_mutex_init(&mExit,NULL);
    pthread_cond_init(&entry, NULL);
    pthread_cond_init(&Exit, NULL);

    pthread_t car;
    pthread_t PLCS_entry_door;
    pthread_t PLCS_exit_door;

    pthread_create(&PLCS_entry_door, NULL, PLCS_entry, NULL);
    cout << "PLCS Entry - Created" << endl;
    pthread_create(&PLCS_exit_door, NULL, PLCS_exit, NULL);
    cout << "PLCS Exit - Created" << endl;
    pthread_create(&car, NULL, CAR, NULL);
    cout << "CAR - Created" << endl;

    while(1){}

    return 0;
}