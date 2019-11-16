#ifndef _ANTEATER_CPP
#define _ANTEATER_CPP

#include <iostream>
#include "Organism.h"
#include "Anteater.h"
using namespace std;

Anteater::Anteater() {  };

bool Anteater::move() {
  for (int i = -TONGUE_LENGTH_ii; i <= TONGUE_LENGTH_ii; i++) {
    int workRow_ii = m_row_ii + i;
    if (workRow_ii >= 0 && workRow_ii < m_world_prob->height()) {
      if (m_world_prob->organism(workRow_ii, m_col_ii)) {
        return 0;
      };
    };
  };
  for (int j = -TONGUE_LENGTH_ii; j <= TONGUE_LENGTH_ii; j++) {
    int workCol_ii = m_col_ii + j;
    if (workCol_ii >= 0 && workCol_ii < m_world_prob->width()) {
      if (m_world_prob->organism(m_row_ii, workCol_ii)) {
        return 0;
      };
    };
  };

};

Anteater *Anteater::reproduce() {
  
};

Anteater::~Anteater() {
  
};

#endif