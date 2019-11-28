#ifndef _ORGANISM_H
#define _ORGANISM_H

#include <math.h>
#include <vector>
#include "World.h"
#include "nanoSeed.h"

const double PI = 4 * atan(1);
const double RADIANS_TO_BITPAIR = PI / 2;
const int VIBE_CHECK_NOTHING = -1;
const int VIBE_CHECK_OUT_OF_RANGE = -2;

class Organism {
  protected:
  // variables:
    World *m_world = nullptr;
    int m_clock = 0;
    int m_reproductiveClock = 0;
    int m_row = -1;
    int m_column = -1;
    int m_generationLength = -1;
  // accessors:
    std::vector<int> vibeCheck() const;
    int what(const int row, const int column) const;
    std::vector<std::vector<int> > radar(const int distance) const;
  // helper functions:
    int chooseDirection(const std::vector<int> in_veii) const;
  public:
  // constructors:
    Organism();
    Organism(World *world);
  // mutators:
    virtual bool move();
    virtual bool feed(int direction = -1) { return 0; }
    virtual bool checkHunger() { return 0; }
    virtual Organism *checkReproduction() = 0;
    int tick() { return ++m_clock; }
  // accessors:
    virtual identity is() const { return ORGANISM; }
    int age() const { return m_clock; }
    int row() const { return m_row; }
    int column() const { return m_column; }
    int generationLength() const { return m_generationLength; }
    int reproductiveClock() const { return m_reproductiveClock; }
  // linkers:
    void world(World *world) { m_world = world; }
  // destructors:
    virtual ~Organism();
    
};

#endif