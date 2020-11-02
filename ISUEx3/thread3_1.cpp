#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <semaphore.h>
using namespace std;

// pthread_mutex_t m;
sem_t s1;

void* printFunc(void* arg){

    int* sl = (int *)arg;     //typecasting

    int count = 0;
    for(int i = 0; i<10; i++){
        // pthread_mutex_lock(&m);
        sem_wait(&s1);
        cout << "#" << i << " this is Thread " << *sl << endl;
        sem_post(&s1);
        // pthread_mutex_unlock(&m);
        sleep(1);
    }
    return NULL;
}

int main(){
    pthread_t th[2];
    int ID[2] = {0, 1};

    if(sem_init(&s1,0,1) != 0) 
    {
        cout << "Semaphore init Error!" << endl;
        return -1;
    }

    // if(pthread_mutex_init(&m, NULL) != 0) 
    // {
    //     cout << "Mutex init Error!" << endl;
    //     return -1;
    // }

    pthread_create(&th[0], NULL, &printFunc, &ID[0]);
    pthread_create(&th[1], NULL, &printFunc, &ID[1]);

    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);

    sem_destroy(&s1);

    return 0;
}