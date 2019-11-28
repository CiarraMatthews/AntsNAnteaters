#ifndef _ANT_H
#define _ANT_H

#include <iostream>
#include "Organism.h"
#include "World.h"

class Ant : public Organism {
  private:
  // mutators:
    Ant *spawnPolar(const int distance, const int direction);
  public:
  // constructors:
    Ant();
    Ant(const int row, const int column, const int generationLength, World *m_world);
  // accessor:
    identity is() const override { return ANT; };
  // mutator:
    Ant *checkReproduction() override;
  // destructor:
    ~Ant();
};

#endif