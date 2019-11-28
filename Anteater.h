#ifndef _ANTEATER_H
#define _ANTEATER_H

#include <bits/stdc++.h>
#include "Organism.h"

class Anteater : public Organism {
  protected:
  // variables:
    int m_tongueLength_ii = -1;
    int m_hunger_ii = 0;
    int m_starvation_ii = -1;
  // accessors:
    std::vector<int> antsInRange(const int distance_kii) const;
  public:
  // constructors:
    Anteater();
    Anteater(const int row_kii, const int col_kii, const int generationLength_kii, World *world_prob, const int tongueLength_kii, const int starvation_kii);
  // accessors:
    identity is() const override { return ANTEATER; };
    virtual int intelligence() const { return 0; };
    int tongueLength() const { return m_tongueLength_ii; };
    int hunger() const { return m_hunger_ii; };
    int starvation() const { return m_starvation_ii; };
  // mutators:
    bool move() override;
    bool feed(int direction_ii) override;
    bool checkHunger() override;
    Anteater *checkReproduction() override;
  // destructor:
    ~Anteater();
};

#endif