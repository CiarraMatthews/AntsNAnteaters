#ifndef _ANT_CPP
#define _ANT_CPP

#include <iostream>
#include "Organism.h"
using namespace std;

class Ant : public Organism {
  private:
  //variables
  // mutators:
    Ant *spawn(const int row_ii, const int col_ii);
  // accessors:
    //bitset vibeCheck() const;
    
  public:
  //constructors
    Ant();
    Ant(int row_ii, int col_ii);
    /* before moving an anteater check each relevant space with "for loop"
    Not sure if this belongs here
    */
  // mutators:
    bool move();
    Ant *reproduce();
  
    
  bool doesAntExist();
};

#endif