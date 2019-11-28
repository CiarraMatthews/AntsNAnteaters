#ifndef _ORGANISM_H
#define _ORGANISM_H

#include <math.h>
#include <vector>
#include "World.h"
#include "nanoSeed.h"

const double PI_df = 4 * atan(1);
const double RADIANS_TO_BITPAIR_df = PI_df / 2;
const int VIBE_CHECK_NOTHING = -1;
const int VIBE_CHECK_OUT_OF_RANGE = -2;

class Organism {
  protected:
  // variables:
    World *m_world_prob = nullptr;
    int m_clock_ii = 0;
    int m_reproductiveClock_ii = 0;
    int m_row_ii = -1;
    int m_col_ii = -1;
    int m_generationLength_ii = -1;
    // Organism *place(const int row_kii, const int col_kii);
  // accessors:
    std::vector<int> vibeCheck() const;
    int what(const int row_kii, const int col_kii) const;
    std::vector<std::vector<int> > radar(const int distance_kii) const;
  // helper functions:
    int chooseDirection(const std::vector<int> in_veii) const;
  public:
  // constructors:
    Organism();
    Organism(World *world_prob);
  // mutators:
    virtual bool move();
    virtual bool feed(int direction_ii = -1) { return 0; };
    virtual bool checkHunger() { return 0; };
    virtual Organism *checkReproduction() = 0;
    int tick() { return ++m_clock_ii; };
  // accessors:
    virtual identity is() const { return ORGANISM; };
    int age() const { return m_clock_ii; };
    int row() const { return m_row_ii; };
    int col() const { return m_col_ii; };
    int generationLength() const { return m_generationLength_ii; };
    int reproductiveClock() const { return m_reproductiveClock_ii; };
  // linkers:
    void world(World *world_prob) { m_world_prob = world_prob; };
  // destructors:
    virtual ~Organism();
    
};

#endif