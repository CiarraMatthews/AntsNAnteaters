#ifndef _ORGANISM_H
#define _ORGANISM_H

#include <bitset>
#include "World.h"
//#include "nanoSeed.cpp"

class Organism {
  protected:
  // variables:
    World *m_world_prob;
    int m_clock_ii;
    int m_row_ii;
    int m_col_ii;
    Organism *place(const int row_ii, const int col_ii);
  // accessors:
    //virtual std::bitset vibeCheck() const = 0;
  public:
  // constructors:
    Organism();
    Organism(World *world_prob);
  // mutators:
    virtual bool move() = 0;
    virtual Organism *reproduce() = 0; // return value not decided yet
  // accessors:
    int age() const { return m_clock_ii; };
    int row() const { return m_row_ii; };
    int col() const { return m_col_ii; };
  // linkers:
    void world(World *world_prob) { m_world_prob = world_prob; };
  // destructors:
    virtual ~Organism();
    
};

#endif