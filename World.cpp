#ifndef _WORLD_CPP
#define _WORLD_CPP

#include <iostream>
#include "World.h"
#include "Ant.h"
#include "Anteater.h"
#include "IntelligentAnteater.h"
using namespace std;

World::World() {  };

World::World(const int height_kii, const int width_kii) {
  if (height_kii > 0) { m_height_ii = height_kii; };
  if (width_kii > 0) { m_width_ii = width_kii; };
  try {
    m_grid_veveprob.resize(height_kii);
    for (int i = 0; i < height_kii; i++) { m_grid_veveprob.at(i).resize(width_kii); };
  } catch (exception &ex_rob) {
    cerr << "exception in Organism::Organism(): " << ex_rob.what() << endl;
  };
  fillWorld();
};

bool World::rangeCheck(const int row_kii, const int col_kii) {
  return row_kii >= 0 && row_kii < m_height_ii && col_kii >= 0 && col_kii < m_width_ii;
};

Organism *World::coupleOrganism(Organism *in_prob) {
  if (rangeCheck(in_prob->row(), in_prob->col())) {
    if (!organism(in_prob->row(), in_prob->col())) {
      m_grid_veveprob.at(in_prob->row()).at(in_prob->col()) = in_prob;
      return in_prob;
    } else { return m_grid_veveprob.at(in_prob->row()).at(in_prob->col()); };
  };
  return nullptr;
};

Organism *World::uncoupleOrganism(Organism *in_prob) {
  if (rangeCheck(in_prob->row(), in_prob->col())) {
    if (organism(in_prob->row(), in_prob->col())) {
      m_grid_veveprob.at(in_prob->row()).at(in_prob->col()) = nullptr;
      return m_grid_veveprob.at(in_prob->row()).at(in_prob->col());
    } else { return m_grid_veveprob.at(in_prob->row()).at(in_prob->col()); };
  };
  return m_grid_veveprob.at(in_prob->row()).at(in_prob->col());
};

int World::spawnOrganisms(const double density_kdf, const int generationLength_kii, const identity what_kii, const int intelligence_kii, const int tongueLength_kii, const int starvation_kii) {
  // create Organism pointers and place in world randomly
  nanoSeed();
  int accum_ii = 0;
  while (accum_ii < density_kdf * m_width_ii * m_height_ii) { // infinite loop
    switch (what_kii) {
      case ORGANISM:
        break;
      case ANT:
        if (coupleOrganism(new Ant(rand() % m_height_ii, rand() % m_width_ii, generationLength_kii, this))) { accum_ii++; };
        break;
      case ANTEATER:
        switch (intelligence_kii) {
          case 0:
            if (coupleOrganism(new Anteater(rand() % m_height_ii, rand() % m_width_ii, generationLength_kii, this, tongueLength_kii, starvation_kii))) { accum_ii++; };
          case 1:
            if (coupleOrganism(new IntelligentAnteater(rand() % m_height_ii, rand() % m_width_ii, generationLength_kii, this, tongueLength_kii, starvation_kii))) { accum_ii++; };
        };
        break;
    };
    if (countOrganisms() >= m_width_ii * m_height_ii) { return accum_ii; }; // if board is found to be completely full somehow
  };
  return accum_ii;
};

int World::countOrganisms(const int id_ii) const {
  int accum_ii = 0;
  for (int i = 0; i < m_height_ii; i++) {
    for (int j = 0; j < m_width_ii; j++) {
      if (organism(i,j)) {
        if (id_ii == -1) { accum_ii++; } else { accum_ii += (organism(i, j)->is() == id_ii); };
      };
    };
  };
  return accum_ii;
};

void World::fillWorld(){
  for (int row = 0; row < height(); row++) {
		for (int column = 0; column < width(); column++) {
			m_grid_veveprob[row][column] = nullptr;
		}
	}
}

vector<vector<Organism *> > World::index() const {
  vector<vector<Organism *> > ret_veveprob;
  ret_veveprob.resize(IDENTITIES_QTY_ii);
  for (int row = 0; row < m_height_ii; row++) {
		for (int column = 0; column < m_width_ii; column++) {
      if (m_grid_veveprob.at(row).at(column)) {
        ret_veveprob.at(m_grid_veveprob.at(row).at(column)->is()).push_back(m_grid_veveprob.at(row).at(column));
      };
    };
  };
  return ret_veveprob;
};

int World::step() {
  m_age_ii++;
  cout << "incremented age" << endl;
  for (int i = 0; i < m_height_ii; i++) {
    for (int j = 0; j < m_width_ii; j++) {
      if (m_grid_veveprob.at(i).at(j)) { m_grid_veveprob.at(i).at(j)->tick(); };
    };
  };
  cout << "ticked all organisms" << endl;
  vector<vector<Organism *> > index_veveprob = index();
  for (Organism *val_prob : index_veveprob.at(ANTEATER)) { val_prob->move(); };
  cout << "moved anteaters" << endl;
  index_veveprob = index();
  for (Organism *val_prob : index_veveprob.at(ANTEATER)) { val_prob->feed(); };
  cout << "anteaters feeded" << endl;
  index_veveprob = index();
  for (Organism *val_prob : index_veveprob.at(ANT)) { val_prob->move(); };
  cout << "moved ants" << endl;
  index_veveprob = index();
  for (Organism *val_prob : index_veveprob.at(ANT)) { val_prob->checkReproduction(); };
  cout << "ants reproduced" << endl;
  index_veveprob = index();
  for (Organism *val_prob : index_veveprob.at(ANTEATER)) { val_prob->checkReproduction(); };
  cout << "anteaters reproduced" << endl;
  index_veveprob = index();
  for (Organism *val_prob : index_veveprob.at(ANTEATER)) { val_prob->checkHunger(); };
  cout << "anteaters starved" << endl;
  return m_age_ii;
};

ostream &operator <<(ostream &ret_ros, const World &world_krob) {
  ret_ros << "age of world: " << world_krob.m_age_ii << endl;
  ret_ros << "ants: " << world_krob.countOrganisms(ANT) << endl;
  ret_ros << "anteaters: " << world_krob.countOrganisms(ANTEATER) << endl << endl;
  for (int i = 0; i < 2 * world_krob.m_width_ii + 3; i++) { ret_ros << "#"; };
  ret_ros << endl;
  for (int row = 0; row < world_krob.m_height_ii; row++) {
    ret_ros << "# ";
		for (int column = 0; column < world_krob.m_width_ii; column++) {
			if (world_krob.m_grid_veveprob.at(row).at(column)) {
        switch (world_krob.m_grid_veveprob.at(row).at(column)->is()) {
          case ANT:
            ret_ros << 'a';
            break;
          case ANTEATER:
            ret_ros << (static_cast<Anteater *>(world_krob.m_grid_veveprob.at(row).at(column))->intelligence() ? 'I' : '@');
            break;
          default:
            break;
        };
      } else { ret_ros << '-'; };
      ret_ros << ' ';
		};
    ret_ros << "# " << row << endl;
	};
  for (int i = 0; i < 2 * world_krob.m_width_ii + 3; i++) { ret_ros << "#"; };
  return ret_ros;
};

World::~World() {
  for (int i = 0; i < m_grid_veveprob.size(); i++) {
    for (int j = 0; j < m_grid_veveprob.at(i).size(); j++) {
      if (organism(i, j)) {
        delete organism(i,j);
      };
    };
  };
};

#endif