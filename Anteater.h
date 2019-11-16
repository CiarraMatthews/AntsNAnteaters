#ifndef _ANTEATER_H
#define _ANTEATER_H

#include "Organism.h"

const int TONGUE_LENGTH_ii = 5;

class Anteater : public Organism {

  public:
  // mutators:
    Anteater();
    void spawnAnteaters();
    bool move();
    Anteater *reproduce();
  // destructor:
    ~Anteater();
};

#endif