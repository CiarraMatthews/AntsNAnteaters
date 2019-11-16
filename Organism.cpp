#ifndef _ORGANISM_CPP
#define _ORGANISM_CPP

#include <iostream>
#include "Organism.h"
using namespace std;

Organism::Organism() {
  m_world_prob = nullptr;
};

Organism::Organism(World *world_prob) {
  m_world_prob = world_prob;
};

/* int Organism::vibeCheck(int range_ii) {
  for (int i = -range_ii; i <= range_ii; i++) {
    int workRow_ii = m_row_ii + i;
    if (workRow_ii >= 0 && workRow_ii < m_world_prob->height()) {
      if (m_world_prob->organism(workRow_ii, m_col_ii)) {
        return 0;
      };
    };
  };
  for (int j = -range_ii; j <= range_ii; j++) {
    int workCol_ii = m_col_ii + j;
    if (workCol_ii >= 0 && workCol_ii < m_world_prob->width()) {
      if (m_world_prob->organism(m_row_ii, m_col_ii + j)) {
        return 0;
      };
    };
  };
  return 1;
}; */

Organism::~Organism() {  };

#endif