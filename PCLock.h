/*
  PCLock.h - Library for photocells task
*/

#ifndef PCLock_H
#define PCLock_H

#include <Arduino.h>

#define totalPcs 10

class PCLock {

  public:

    PCLock (int, int, int, int, int, int, int, int, int, int);

    void activatePCs();
    bool checkPCs();

  private:

    int _pc0, _pc1, _pc2, _pc3, _pc4, _pc5, _pc6, _pc7, _pc8, _pc9;
    int _pcArray[totalPcs];
}
