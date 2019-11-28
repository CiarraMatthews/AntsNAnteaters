#ifndef _ORGANISM_CPP
#define _ORGANISM_CPP

#include <iostream>
#include <cmath>
#include "Organism.h"
using namespace std;

Organism::Organism() {  };

Organism::Organism(World *world) {
  m_world = world;
};

vector<int> Organism::vibeCheck() const {
  vector<int> mapping;
  if (m_world->rangeCheck(m_row - 1, m_column)) {
    if (!m_world->organism(m_row - 1, m_column)) { 
      mapping.push_back(NORTH); 
    }
  }
  if (m_world->rangeCheck(m_row, m_column + 1)) {
    if (!m_world->organism(m_row, m_column + 1)) { 
      mapping.push_back(EAST); 
      }
  }
  if (m_world->rangeCheck(m_row + 1, m_column)) {
    if (!m_world->organism(m_row + 1, m_column)) { 
      mapping.push_back(SOUTH); 
    }
  }
  if (m_world->rangeCheck(m_row, m_column - 1)) {
    if (!m_world->organism(m_row, m_column - 1)) { 
      mapping.push_back(WEST); 
    }
  }
  return mapping;
};

int Organism::what(const int row, const int column) const {
  if (!m_world->rangeCheck(row, column)) { 
    return VIBE_CHECK_OUT_OF_RANGE; 
  }
  else if (!m_world->organism(row, column)) { 
    return VIBE_CHECK_NOTHING; 
  }
  else { 
    return m_world->organism(row, column)->is(); 
  }
}

vector<vector<int> > Organism::radar(const int distance) const {
  vector<vector<int> > ret_veveii;
  ret_veveii.resize(DIRECTIONS_QTY);
  for (int offset = 1; offset <= distance; offset++) {
    if (m_world->rangeCheck(m_row - offset, m_column)) {
      ret_veveii.at(NORTH).push_back(what(m_row - offset, m_column));
    }
  }
  for (int offset = 1; offset <= distance; offset++) {
    if (m_world->rangeCheck(m_row, m_column + offset)) {
      ret_veveii.at(EAST).push_back(what(m_row, m_column + offset));
    };
  };
  for (int offset = 1; offset <= distance; offset++) {
    if (m_world->rangeCheck(m_row + offset, m_column)) {
      ret_veveii.at(SOUTH).push_back(what(m_row + offset, m_column));
    };
  };
  for (int offset = 1; offset <= distance; offset++) {
    if (m_world->rangeCheck(m_row, m_column - offset)) {
      ret_veveii.at(WEST).push_back(what(m_row, m_column - offset));
    };
  };
  return ret_veveii;
};

bool Organism::move() {
  int directionChoice = chooseDirection(vibeCheck());
  if (directionChoice >= 0 && directionChoice < DIRECTIONS_QTY) { // confidence check
    switch(directionChoice) {
      case NORTH:
        m_world->uncoupleOrganism(this);
        m_row--;
        m_world->coupleOrganism(this);
        return 1;
      case EAST:
        m_world->uncoupleOrganism(this);
        m_column++;
        m_world->coupleOrganism(this);
        return 1;
      case SOUTH:
        m_world->uncoupleOrganism(this);
        m_row++;
        m_world->coupleOrganism(this);
        return 1;
      case WEST:
        m_world->uncoupleOrganism(this);
        m_column--;
        m_world->coupleOrganism(this);
        return 1;
      default:
        return 0;
    };
  } 
  else { 
    return 0; 
  }
}

int Organism::chooseDirection(const vector<int> in_veii) const {
  if (in_veii.size() == 0) { 
    return -1; 
  }
  else if (in_veii.size() == 1) { 
    return in_veii.at(0); 
  }
  else {
    nanoSeed();
    int random = rand() % in_veii.size();
    return in_veii.at(random);
  }
}

Organism::~Organism() { 
  m_world->uncoupleOrganism(this);
}

#endif