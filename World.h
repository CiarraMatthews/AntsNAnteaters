#ifndef _WORLD_H
#define _WORLD_H

#include <vector>

//added forward declaration
class Organism;

class World {
  private:
  // variables:
    int m_height_ii;
    int m_width_ii;
    int m_age_ii;
    std::vector<std::vector<Organism *> > m_grid_veveprob;
  public:
  // constructors:
    World();
    World(int height_ii, int width_ii);
    World(const World &world_krob);
  // mutators:
    Organism *addOrganism(int row_ii, int col_ii);
    //I guess these go here :?
    void spawnAnts();
    void spawnAnteaters();
    void fillWorld();
  // accessors:
    friend std::ostream &operator <<(std::ostream &ret_ros, const World &world_krob);
    int height() { return m_height_ii; };
    int width() { return m_width_ii; };
  // finders:
    Organism *organism(int row_ii, int col_ii) { return m_grid_veveprob.at(row_ii).at(col_ii); };
};

#endif