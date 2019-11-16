#include <iostream>
#include "Ant.h"

Ant::Ant() {
  
};

Ant::Ant(int row_ii, int col_ii) {
  m_row_ii = row_ii;
  m_col_ii = col_ii;
  if (m_row_ii >= 0 && m_row_ii < m_world_prob->height()) {
    if (m_col_ii >= 0 && m_col_ii < m_world_prob->width()) {
      m_world_prob->addOrganism(row_ii, col_ii);
    };
  };
};

/*bitset<4> Ant::vibeCheck() const {
  bitset<4> ret_ob;
  if (m_world_prob->organism(m_row_ii - 1, m_col_ii)) { ret_ob.set(0); }; // north
  if (m_world_prob->organism(m_row_ii, m_col_ii + 1)) { ret_ob.set(1); }; // east
  if (m_world_prob->organism(m_row_ii + 1, m_col_ii)) { ret_ob.set(2); }; // south
  if (m_world_prob->organism(m_row_ii, m_col_ii - 1)) { ret_ob.set(3); }; // west
  return ret_ob;
};*/

Ant *Ant::reproduce() {
  /*bitset<4> field_ob = vibeCheck();
  if (field_ob.count() < 2) {
    if (field_ob.test(0)) { spawn(m_row_ii - 1, m_col_ii); } // north
    else if (field_ob.test(1)) { spawn(m_row_ii, m_col_ii + 1); } // east
    else if (field_ob.test(2)) { spawn(m_row_ii + 1, m_col_ii); } // south
    else if (field_ob.test(3)) { spawn(m_row_ii, m_col_ii - 1); } // west
    else { return nullptr; }; // there was no space available
  } else {
    nanoSeed();
    int random_ii = rand() % field_ob.count();
    // figure out how to spawn according to the random-th set bit in field
  };*/
};

Ant *Ant::spawn(const int row_ii, const int col_ii) {
  Ant *newAnt_prob = new Ant(row_ii, col_ii);
  return newAnt_prob;
};