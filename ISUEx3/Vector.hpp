#ifndef VECTOR_HPP_
#define VECTOR_HPP_
#include <pthread.h>
#include <semaphore.h>
//=======================================================
// Class: Vector
// contains a size_-size vector of integers.
// Use the function setAndTest to set all elements
// of the vector to a certain value and then test that
// the value is indeed correctly set
//=======================================================

class Vector
{
public:
   Vector(unsigned int size = 10000) : size_(size)
      {
         pthread_mutex_init(&m, NULL);     //Mutex
         //sem_init(&s,0,1);                   //Semaphore
         vector_ = new int[size_];
         set(0);
      }

   ~Vector()
      {
         delete[] vector_;
         pthread_mutex_destroy(&m);
         //sem_destroy(&s);
      }

   bool setAndTest(int n)
      {
         pthread_mutex_lock(&m);       //Lock
         //sem_wait(&s);
         set(n);
         bool testResult = test(n);
         pthread_mutex_unlock(&m);     //Unlock
         //sem_post(&s);
         return testResult;
      }

private:
   void set(int n)
      {
         for(unsigned int i=0; i<size_; i++) vector_[i] = n;
      }

   bool test(int n)
      {
         for(unsigned int i=0; i<size_; i++) if(vector_[i] != n) return false;
         return true;
      }

   int*           vector_;
   unsigned int   size_;
   pthread_mutex_t m;
   //sem_t s;
};

#endif
