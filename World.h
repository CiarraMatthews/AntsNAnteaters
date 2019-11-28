#ifndef _WORLD_H
#define _WORLD_H

#include <algorithm>
#include <vector>

const int DIRECTIONS_QTY = 4;
enum direction { NORTH, EAST, SOUTH, WEST };

const int IDENTITIES_QTY = 3;
enum identity { ORGANISM, ANT, ANTEATER };

class Organism; // forward declaration

class World {
  private:
  // variables:
    int m_height;
    int m_width;
    int m_age = 0;
    std::vector<std::vector<Organism *> > m_grid;
  // mutators:
    void fillWorld();
  public:
  // constructors:
    World();
    World(const int height, const int width);
    World(const World &world);
  // mutators:
    Organism *coupleOrganism(Organism *);
    Organism *uncoupleOrganism(Organism *);
    int spawnOrganisms(const double density_kdf, const int generationLength_kii, const identity what_kii, const int intelligence_kii = 0, const int tongueLength_kii = 0, const int starvation_kii = 0);
    int step();
  // accessors:
    friend std::ostream &operator <<(std::ostream &ret_ros, const World &world);
    int height() const { return m_height; };
    int width() const { return m_width; };
    int countOrganisms(const int id = -1) const;
    bool rangeCheck(const int row, const int column);
    std::vector<std::vector<Organism *> > index();
  // finders:
    Organism *organism(int row, int column) const { return m_grid.at(row).at(column); }
  // destructor:
    ~World();
};

#endif