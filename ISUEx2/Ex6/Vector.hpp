#ifndef VECTOR_HPP_
#define VECTOR_HPP_
#include <iostream>
using namespace std;

//=======================================================
// Class: Vector
// contains a size_-size vector of integers.
// Use the function setAndTest to set all elements
// of the vector to a certain value and then test that
// the value is indeed correctly set
//=======================================================
unsigned int f = 0;

class Vector
{
public:
   Vector(unsigned int size = 100) : size_(size)
      {
         if(f == 0){
            cout << "Objects in Vectors: " << size << endl;
            f = 1;
         }
         vector_ = new int[size_];
         set(0);
      }

   ~Vector()
      {
         delete[] vector_;
      }

   bool setAndTest(int n)
      {
         set(n);
         return test(n);
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
};

#endif
