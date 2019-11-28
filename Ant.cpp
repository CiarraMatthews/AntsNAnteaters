#ifndef _ANT_CPP
#define _ANT_CPP

#include <iostream>
#include "Ant.h"
#include "Organism.h"
#include "World.h"

using namespace std;

Ant::Ant() {  };

Ant::Ant(const int row_kii, const int col_kii, const int generationLength_kii, World *world_prob) {
  m_row_ii = row_kii;
  m_col_ii = col_kii;
  m_generationLength_ii = generationLength_kii;
  m_world_prob = world_prob;
  m_world_prob->coupleOrganism(this);
};

Ant *Ant::checkReproduction() {
  if (m_reproductiveClock_ii >= m_generationLength_ii) {
    m_reproductiveClock_ii = 0;
    int direction_ii = chooseDirection(vibeCheck());
    if (direction_ii >= 0 && direction_ii < DIRECTIONS_QTY_ii) {
      int newRow_ii = m_row_ii - cos(direction_ii * RADIANS_TO_BITPAIR_df);
      int newCol_ii = m_col_ii + sin(direction_ii * RADIANS_TO_BITPAIR_df);
      Ant *ret_prob = new Ant(newRow_ii, newCol_ii, m_generationLength_ii, m_world_prob);
      return ret_prob;
    };
    return nullptr;
  } else {
    m_reproductiveClock_ii++;
    return nullptr;
  };
};

Ant::~Ant() {  };

#endif