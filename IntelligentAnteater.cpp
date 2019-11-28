#ifndef _INTELLIGENT_ANTEATER_CPP
#define _INTELLIGENT_ANTEATER_CPP

#include <iostream>
#include "IntelligentAnteater.h"
using namespace std;

IntelligentAnteater::IntelligentAnteater() {  };

IntelligentAnteater::IntelligentAnteater(const int row, const int column, const int generationLength, World *world, const int tongueLength, const int starvation) {
  m_row = row;
  m_column = column;
  m_generationLength = generationLength;
  m_world = world;
  m_tongueLength= tongueLength;
  m_starvation = starvation;
  m_world->coupleOrganism(this);
};

bool IntelligentAnteater::feed(int direction) {
  vector<vector<int> > radarVec = radar(m_tongueLength);
  vector<int> valid_veii;
  for (int direction = 0; direction < radarVec.size(); direction++) {
    if (radarVec.at(direction).size() == m_tongueLength) {
      if (count(radarVec.at(direction).begin(), radarVec.at(direction).end(), ANTEATER) == 0) {
        if (count(radarVec.at(direction).begin(), radarVec.at(direction).end(), ANT)) {
          valid_veii.push_back(direction);
        }
      }
    }
  }
  direction = chooseDirection(valid_veii);
  if (direction >= 0 && direction < DIRECTIONS_QTY) {
    return Anteater::feed(direction);
  } 
  else {
    m_hunger++;
    return 0;
  }
}

IntelligentAnteater::~IntelligentAnteater() {  };

#endif