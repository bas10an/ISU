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
    pthread_t th[2];
    string name0 = "incrementer";
    string name1 = "reader";
    unsigned int shared = 0;
    pthread_create(&th[0], NULL, &incrementer, &shared);
    pthread_create(&th[1], NULL, &reader, &shared);
    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);
    cout << "Main: Exiting" << endl;
    return 0;
}