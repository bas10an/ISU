#include <pthread.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void* printFunc(void* arg){
    string* sl = (string *)arg;     //typecasting
    int count = 0;
    for(int i = 0; i<10; i++){
        cout << "#" << i << " this is " << *sl << endl;
        sleep(1);
    }
    cout << *sl << " terminates" << endl;
    return NULL;
}
int main(){
    pthread_t th[2];
    string name0 = "Thread 0";
    string name1 = "Thread 1";
    pthread_create(&th[0], NULL, &printFunc, &name0);
    pthread_create(&th[1], NULL, &printFunc, &name1);
    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);
    cout << "Main: Exiting" << endl;
    return 0;
}