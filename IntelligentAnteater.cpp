#ifndef _INTELLIGENT_ANTEATER_CPP
#define _INTELLIGENT_ANTEATER_CPP

#include <iostream>
#include "IntelligentAnteater.h"
using namespace std;

IntelligentAnteater::IntelligentAnteater() {  };

IntelligentAnteater::IntelligentAnteater(const int row_kii, const int col_kii, const int generationLength_kii, World *world_prob, const int tongueLength_kii, const int starvation_kii) {
  m_row_ii = row_kii;
  m_col_ii = col_kii;
  m_generationLength_ii = generationLength_kii;
  m_world_prob = world_prob;
  m_tongueLength_ii = tongueLength_kii;
  m_starvation_ii = starvation_kii;
  m_world_prob->coupleOrganism(this);
};

bool IntelligentAnteater::feed(int direction_ii) {
  vector<vector<int> > radar_veveii = radar(m_tongueLength_ii);
  vector<int> valid_veii;
  for (int direction_ii = 0; direction_ii < radar_veveii.size(); direction_ii++) {
    if (radar_veveii.at(direction_ii).size() == m_tongueLength_ii) {
      if (count(radar_veveii.at(direction_ii).begin(), radar_veveii.at(direction_ii).end(), ANTEATER) == 0) {
        if (count(radar_veveii.at(direction_ii).begin(), radar_veveii.at(direction_ii).end(), ANT)) {
          valid_veii.push_back(direction_ii);
        };
      };
    };
  };
  direction_ii = chooseDirection(valid_veii);
  if (direction_ii >= 0 && direction_ii < DIRECTIONS_QTY_ii) {
    return Anteater::feed(direction_ii);
  } else {
    m_hunger_ii++;
    return 0;
  };
};

IntelligentAnteater::~IntelligentAnteater() {  };

#endif