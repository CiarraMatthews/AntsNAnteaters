#ifndef _ANTEATER_CPP
#define _ANTEATER_CPP

#include <iostream>
#include "Organism.h"
#include "Anteater.h"
#include "IntelligentAnteater.h"
#include "Ant.h"
using namespace std;

Anteater::Anteater() {  };

Anteater::Anteater(const int row_kii, const int col_kii, const int generationLength_kii, World *world_prob, const int tongueLength_kii, const int starvation_kii) {
  m_row_ii = row_kii;
  m_col_ii = col_kii;
  m_generationLength_ii = generationLength_kii;
  m_world_prob = world_prob;
  m_tongueLength_ii = tongueLength_kii;
  m_starvation_ii = starvation_kii;
  m_world_prob->coupleOrganism(this);
};

vector<int> Anteater::antsInRange(const int distance_kii) const {
  vector<vector<int> > radar_veveii = radar(distance_kii);
  vector<int> ret_veii;
  for (int direction_ii = 0; direction_ii < DIRECTIONS_QTY_ii; direction_ii++) {
    if (count(radar_veveii.at(direction_ii).begin(), radar_veveii.at(direction_ii).end(), ANT)) {
      ret_veii.push_back(direction_ii);
    };
  };
  cout << "vector antsInRange size " << ret_veii.size() << endl;
  return ret_veii;
};

bool Anteater::move() {
  if (antsInRange(m_tongueLength_ii).size()) { return 0; }
  else {
    // this needs to move towards the NEAREST (Manhattan distance) ant on the board.
    // currently it just moves randomly.
    return Organism::move();
  };
};

bool Anteater::checkHunger() {
  cout << this << " anteater hunger at " << m_hunger_ii << endl;
  if (m_hunger_ii >= m_starvation_ii) {
    delete this;
    return 1; // to get rid of a warning
  } else { return 0; };
};

Anteater *Anteater::checkReproduction() {
  if (m_reproductiveClock_ii >= m_generationLength_ii) {
    m_reproductiveClock_ii = 0;
    int direction_ii = chooseDirection(vibeCheck());
    if (direction_ii == -1) {
      vector<vector<int> > radar_veveii = radar(1);
      vector<int> temp_veii;
      for (int direction_ii = 0; direction_ii < radar_veveii.size(); direction_ii++) {
        if (radar_veveii.at(direction_ii).size()) {
          if (radar_veveii.at(direction_ii).at(0) == ANT) { temp_veii.push_back(direction_ii); };
        };
      };
      direction_ii = chooseDirection(temp_veii);
    };
    if (direction_ii == -1) {
      return nullptr;
    } else {
      int newRow_ii = m_row_ii - cos(direction_ii * RADIANS_TO_BITPAIR_df);
      int newCol_ii = m_col_ii + sin(direction_ii * RADIANS_TO_BITPAIR_df);
      if (m_world_prob->organism(newRow_ii, newCol_ii)) { delete m_world_prob->organism(newRow_ii, newCol_ii); };
      Anteater *ret_prob = nullptr;
      if (intelligence()) {
        ret_prob = new IntelligentAnteater(newRow_ii, newCol_ii, m_generationLength_ii, m_world_prob, m_tongueLength_ii, m_starvation_ii);
      } else {
        ret_prob = new Anteater(newRow_ii, newCol_ii, m_generationLength_ii, m_world_prob, m_tongueLength_ii, m_starvation_ii);
      };
      return ret_prob;
    };
  } else {
    m_reproductiveClock_ii++;
    return nullptr;
  };
};

bool Anteater::feed(int direction_ii) {
  if (direction_ii == -1) { direction_ii = chooseDirection(antsInRange(m_tongueLength_ii)); };
  if (direction_ii == -1) { 
    m_hunger_ii++;
    return 0;
  };
  cout << "direction chosen was " << direction_ii << endl;
  vector<int> killQueue_veii;
  vector<vector<int> > radar_veveprob = radar(m_tongueLength_ii);
  if (radar_veveprob.at(direction_ii).size() < m_tongueLength_ii) {  // will hit a wall
    cout << "EAT WALL." << endl;
    m_hunger_ii++;
    return 0;
  };
  for (int i = 0; i < radar_veveprob.at(direction_ii).size(); i++) {
    switch (radar_veveprob.at(direction_ii).at(i)) {
      case ORGANISM:
        cerr << "organism?" << endl;
        break;
      case ANT:
        killQueue_veii.push_back(i + 1);
        cout << "kill queue at " << killQueue_veii.size() << endl;
        break;
      case ANTEATER:
        cout << "EAT AARD." << endl;
        m_hunger_ii++;
        return 0;
    };
  };
  for (int j = 0; j < killQueue_veii.size(); j++) {
    switch (direction_ii) {
      case NORTH:
        cout << "deleting at distance " << killQueue_veii.at(j) << endl;
        delete m_world_prob->organism(m_row_ii - killQueue_veii.at(j), m_col_ii);
        break;
      case EAST:
        cout << "deleting at distance " << killQueue_veii.at(j) << endl;
        delete m_world_prob->organism(m_row_ii, m_col_ii + killQueue_veii.at(j));
        break;
        case SOUTH:
        cout << "deleting at distance " << killQueue_veii.at(j) << endl;
        delete m_world_prob->organism(m_row_ii + killQueue_veii.at(j), m_col_ii);
        break;
      case WEST:
        cout << "deleting at distance " << killQueue_veii.at(j) << endl;
        delete m_world_prob->organism(m_row_ii, m_col_ii - killQueue_veii.at(j));
        break;
      default:
        cerr << "what?";
        cout << "EAT FAIL." << endl;
        m_hunger_ii++;
        return 0;
    };
  };
  m_hunger_ii = 0;
  cout << "ate correctly." << endl;
  return 1;
};

Anteater::~Anteater() {  };

#endif