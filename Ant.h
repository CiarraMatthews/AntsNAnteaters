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
    Ant(const int row_kii, const int col_kii, const int generationLength_kii, World *m_world_prob);
  // accessor:
    identity is() const override { return ANT; };
  // mutator:
    Ant *checkReproduction() override;
  // destructor:
    ~Ant();
};

#endif