#ifndef _ANTEATER_CPP
#define _ANTEATER_CPP

#include <iostream>
#include "Organism.h"
#include "Anteater.h"
#include "IntelligentAnteater.h"
#include "Ant.h"
using namespace std;

Anteater::Anteater() {  }

Anteater::Anteater(const int row, const int column, const int generationLength, World *world, const int tongueLength, const int starvation) {
  m_row = row;
  m_column = column;
  m_generationLength = generationLength;
  m_world = world;
  m_tongueLength = tongueLength;
  m_starvation = starvation;
  m_world->coupleOrganism(this);
}

vector<int> Anteater::antsInRange(const int distance) const {
  vector<vector<int> > radarVec = radar(distance);
  vector<int> nearbyAnts;
  for (int direction = 0; direction < DIRECTIONS_QTY; direction++) {
    if (count(radarVec.at(direction).begin(), radarVec.at(direction).end(), ANT)) {
      nearbyAnts.push_back(direction);
    }
  }
  return nearbyAnts;
}

Ant *Anteater::findNearestAnt() const {
  int distance = 0, shortestDistance = 500;
  vector<Ant *> nearestAnts;
  //this ant for loop belongs in the move function, right?

  vector<vector<Organism *> > indexVec = m_world->index();
  for (Organism *val_prob : indexVec.at(ANT)) { 
    distance = (abs(val_prob->column() - column()) + abs(val_prob->row() - row()));
    if (distance < shortestDistance){
      shortestDistance = distance;
      nearestAnts.push_back(static_cast<Ant *>(val_prob));
    }
  }

  return nearestAnts.at(rand() % nearestAnts.size());
  
}

bool Anteater::move() {
  if (antsInRange(m_tongueLength).size()) { 
    return 0; 
    }
  else {
    
    // this needs to move towards the NEAREST (Manhattan distance) ant on the board.
    // currently it just moves randomly.
    return Organism::move();
  }
}

bool Anteater::checkHunger() {
  if (m_hunger >= m_starvation) {
    delete this;
    // to get rid of a warning
    return 1; 
  } 
  else { 
      return 0; 
  }
}

Anteater *Anteater::checkReproduction() {
  if (m_reproductiveClock >= m_generationLength) {
    m_reproductiveClock = 0;
    int direction = chooseDirection(vibeCheck());
    if (direction == -1) {
      vector<vector<int> > radarVec = radar(1);
      vector<int> temp_veii;
      for (int direction = 0; direction < radarVec.size(); direction++) {
        if (radarVec.at(direction).size()) {
          if (radarVec.at(direction).at(0) == ANT) { temp_veii.push_back(direction); };
        }
      }
      direction = chooseDirection(temp_veii);
    }
    if (direction == -1) {
      return nullptr;
    } 
    else {
      int newRow = m_row - cos(direction * RADIANS_TO_BITPAIR);
      int newColumn = m_column + sin(direction * RADIANS_TO_BITPAIR);
      if (m_world->organism(newRow, newColumn)) { 
        delete m_world->organism(newRow, newColumn); 
      }
      Anteater *ret_prob = nullptr;
      if (this->intelligence()) {
        ret_prob = new IntelligentAnteater(newRow, newColumn, m_generationLength, m_world, m_tongueLength, m_starvation);
      } 
      else {
        ret_prob = new Anteater(newRow, newColumn, m_generationLength, m_world, m_tongueLength, m_starvation);
      }
      return ret_prob;
    }
  } 
  else {
    m_reproductiveClock++;
    return nullptr;
  }
}

bool Anteater::feed(int direction) {
  if (direction == -1) { 
    direction = chooseDirection(antsInRange(m_tongueLength)); 
  }
  if (direction == -1) { 
    m_hunger++;
    return 0;
  }
  vector<int> killQueue;
  vector<vector<int> > radar_veveprob = radar(m_tongueLength);
  // will hit a wall
  if (radar_veveprob.at(direction).size() < m_tongueLength) {  
    m_hunger++;
    return 0;
  };
  for (int i = 0; i < radar_veveprob.at(direction).size(); i++) {
    switch (radar_veveprob.at(direction).at(i)) {
      case ORGANISM:
        cerr << "organism?" << endl;
        break;
      case ANT:
        killQueue.push_back(i + 1);
        break;
      case ANTEATER:
        cout << "EAT AARD." << endl;
        m_hunger++;
        return 0;
    }
  }
  for (int j = 0; j < killQueue.size(); j++) {
    switch (direction) {
      case NORTH:
        delete m_world->organism(m_row - killQueue.at(j), m_column);
        break;
      case EAST:
        delete m_world->organism(m_row, m_column + killQueue.at(j));
        break;
        case SOUTH:
        delete m_world->organism(m_row + killQueue.at(j), m_column);
        break;
      case WEST:
        delete m_world->organism(m_row, m_column - killQueue.at(j));
        break;
      default:
        cerr << "what?";
        m_hunger++;
        return 0;
    }
  }
  m_hunger = 0;
  return 1;
}

Anteater::~Anteater() {  }

#endif