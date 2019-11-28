#ifndef _ORGANISM_CPP
#define _ORGANISM_CPP

#include <iostream>
#include <cmath>
#include "Organism.h"
using namespace std;

Organism::Organism() {  };

Organism::Organism(World *world_prob) {
  m_world_prob = world_prob;
};

vector<int> Organism::vibeCheck() const {
  vector<int> ret_veii;
  if (m_world_prob->rangeCheck(m_row_ii - 1, m_col_ii)) {
    if (!m_world_prob->organism(m_row_ii - 1, m_col_ii)) { ret_veii.push_back(NORTH); };
  };
  if (m_world_prob->rangeCheck(m_row_ii, m_col_ii + 1)) {
    if (!m_world_prob->organism(m_row_ii, m_col_ii + 1)) { ret_veii.push_back(EAST); };
  };
  if (m_world_prob->rangeCheck(m_row_ii + 1, m_col_ii)) {
    if (!m_world_prob->organism(m_row_ii + 1, m_col_ii)) { ret_veii.push_back(SOUTH); };
  };
  if (m_world_prob->rangeCheck(m_row_ii, m_col_ii - 1)) {
    if (!m_world_prob->organism(m_row_ii, m_col_ii - 1)) { ret_veii.push_back(WEST); };
  };
  return ret_veii;
};

int Organism::what(const int row_kii, const int col_kii) const {
  if (!m_world_prob->rangeCheck(row_kii, col_kii)) { return VIBE_CHECK_OUT_OF_RANGE; }
  else if (!m_world_prob->organism(row_kii, col_kii)) { return VIBE_CHECK_NOTHING; }
  else { return m_world_prob->organism(row_kii, col_kii)->is(); };
};

vector<vector<int> > Organism::radar(const int distance_kii) const {
  vector<vector<int> > ret_veveii;
  ret_veveii.resize(DIRECTIONS_QTY_ii);
  for (int offset_ii = 1; offset_ii <= distance_kii; offset_ii++) {
    if (m_world_prob->rangeCheck(m_row_ii - offset_ii, m_col_ii)) {
      ret_veveii.at(NORTH).push_back(what(m_row_ii - offset_ii, m_col_ii));
    };
  };
  for (int offset_ii = 1; offset_ii <= distance_kii; offset_ii++) {
    if (m_world_prob->rangeCheck(m_row_ii, m_col_ii + offset_ii)) {
      ret_veveii.at(EAST).push_back(what(m_row_ii, m_col_ii + offset_ii));
    };
  };
  for (int offset_ii = 1; offset_ii <= distance_kii; offset_ii++) {
    if (m_world_prob->rangeCheck(m_row_ii + offset_ii, m_col_ii)) {
      ret_veveii.at(SOUTH).push_back(what(m_row_ii + offset_ii, m_col_ii));
    };
  };
  for (int offset_ii = 1; offset_ii <= distance_kii; offset_ii++) {
    if (m_world_prob->rangeCheck(m_row_ii, m_col_ii - offset_ii)) {
      ret_veveii.at(WEST).push_back(what(m_row_ii, m_col_ii - offset_ii));
    };
  };
  return ret_veveii;
};

bool Organism::move() {
  int directionChoice_ii = chooseDirection(vibeCheck());
  if (directionChoice_ii >= 0 && directionChoice_ii < DIRECTIONS_QTY_ii) { // confidence check
    switch(directionChoice_ii) {
      case NORTH:
        m_world_prob->uncoupleOrganism(this);
        m_row_ii--;
        m_world_prob->coupleOrganism(this);
        return 1;
      case EAST:
        m_world_prob->uncoupleOrganism(this);
        m_col_ii++;
        m_world_prob->coupleOrganism(this);
        return 1;
      case SOUTH:
        m_world_prob->uncoupleOrganism(this);
        m_row_ii++;
        m_world_prob->coupleOrganism(this);
        return 1;
      case WEST:
        m_world_prob->uncoupleOrganism(this);
        m_col_ii--;
        m_world_prob->coupleOrganism(this);
        return 1;
      default:
        return 0;
    };
  } else { return 0; };
};

int Organism::chooseDirection(const vector<int> in_veii) const {
  if (in_veii.size() == 0) { return -1; }
  else if (in_veii.size() == 1) { return in_veii.at(0); }
  else {
    nanoSeed();
    int random_ii = rand() % in_veii.size();
    return in_veii.at(random_ii);
  };
};

Organism::~Organism() { 
  m_world_prob->uncoupleOrganism(this);
};

#endif