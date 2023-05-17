#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
using namespace std;

namespace ProjectLibrary
{
  class Empty
  {
    public:
      void Show() const {cout<< "Hello world;"<< endl; }
      void Print() const {cout << "Questo progetto sarà copmplicato" << endl;}
  };
}

#endif // __EMPTY_H
