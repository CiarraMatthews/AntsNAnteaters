#ifndef _ANTEATER_H
#define _ANTEATER_H

#include <bits/stdc++.h>
#include "Organism.h"

class Ant;

class Anteater : public Organism {
  protected:
  // variables:
    int m_tongueLength = -1;
    int m_hunger = 0;
    int m_starvation = -1;
  // accessors:
    std::vector<int> antsInRange(const int distance) const;
    Ant *findNearestAnt() const;
  public:
  // constructors:
    Anteater();
    Anteater(const int row, const int column, const int generationLength, World *world, const int tongueLength, const int starvation);
  // accessors:
    identity is() const override { return ANTEATER; }
    virtual int intelligence() const { return 0; }
    int tongueLength() const { return m_tongueLength; }
    int hunger() const { return m_hunger; }
    int starvation() const { return m_starvation; }
  // mutators:
    bool move() override;
    bool feed(int direction) override;
    bool checkHunger() override;
    Anteater *checkReproduction() override;
  // destructor:
    ~Anteater();
};

#endif