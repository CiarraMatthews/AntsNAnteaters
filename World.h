#ifndef _WORLD_H
#define _WORLD_H

#include <algorithm>
#include <vector>

const int DIRECTIONS_QTY_ii = 4;
enum direction { NORTH, EAST, SOUTH, WEST };

const int IDENTITIES_QTY_ii = 3;
enum identity { ORGANISM, ANT, ANTEATER };

class Organism; // forward declaration

class World {
  private:
  // variables:
    int m_height_ii;
    int m_width_ii;
    int m_age_ii = 0;
    std::vector<std::vector<Organism *> > m_grid_veveprob;
  // mutators:
    void fillWorld();
  public:
  // constructors:
    World();
    World(const int height_kii, const int width_kii);
    World(const World &world_krob);
  // mutators:
    Organism *coupleOrganism(Organism *);
    Organism *uncoupleOrganism(Organism *);
    int spawnOrganisms(const double density_kdf, const int generationLength_kii, const identity what_kii, const int intelligence_kii = 0, const int tongueLength_kii = 0, const int starvation_kii = 0);
    int step();
  // accessors:
    friend std::ostream &operator <<(std::ostream &ret_ros, const World &world_krob);
    int height() const { return m_height_ii; };
    int width() const { return m_width_ii; };
    int countOrganisms(const int id_ii = -1) const;
    bool rangeCheck(const int row_kii, const int col_kii);
    std::vector<std::vector<Organism *> > index() const;
  // finders:
    Organism *organism(int row_ii, int col_ii) const { return m_grid_veveprob.at(row_ii).at(col_ii); };
  // destructor:
    ~World();
};

#endif