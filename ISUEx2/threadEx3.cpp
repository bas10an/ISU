#include <pthread.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void* incrementer(void* data){
    for(int i = 0; i<10; i++){
        (*(int*)data)++;
        sleep(1);
    }
    cout << "Incrementer" << " terminates" << endl;
    return NULL;
}
void* reader(void* data){
    for(int i = 0; i<10; i++){
        cout << "Read: " << (*(int*)data) << endl;
        sleep(1);
    }
    cout << "Reader" << " terminates" << endl;
    return NULL;
}
int main(){
    pthread_t inc;
    pthread_t read;
    unsigned int shared = 0;
    pthread_create(&inc, NULL, &incrementer, &shared);
    pthread_create(&read, NULL, &reader, &shared);
    pthread_join(inc,NULL);
    pthread_join(read,NULL);
    cout << "Main: Exiting" << endl;
    return 0;
}