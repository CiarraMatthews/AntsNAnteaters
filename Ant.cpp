#ifndef _ANT_CPP
#define _ANT_CPP

#include <iostream>
#include "Ant.h"
#include "Organism.h"
#include "World.h"

using namespace std;

Ant::Ant() {  }

Ant::Ant(const int row, const int column, const int generationLength, World *world) {
  m_row = row;
  m_column = column;
  m_generationLength = generationLength;
  m_world = world;
  m_world->coupleOrganism(this);
}


Ant *Ant::checkReproduction() {
  if (m_reproductiveClock >= m_generationLength) {
    m_reproductiveClock = 0;
    int direction = chooseDirection(vibeCheck());
    if (direction >= 0 && direction < DIRECTIONS_QTY) {
      int newRow = m_row - cos(direction * RADIANS_TO_BITPAIR);
      int newColumn = m_column + sin(direction * RADIANS_TO_BITPAIR);
      Ant *antPtr = new Ant(newRow, newColumn, m_generationLength, m_world);
      return antPtr;
    }
    return nullptr;
  } 
  else {
    m_reproductiveClock++;
    return nullptr;
  }
}

Ant::~Ant() {  }

#endif