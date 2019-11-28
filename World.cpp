#ifndef _WORLD_CPP
#define _WORLD_CPP

#include <iostream>
#include "World.h"
#include "Ant.h"
#include "Anteater.h"
#include "IntelligentAnteater.h"
using namespace std;

World::World() {  };

World::World(const int height, const int width) {
  if (height > 0) {
    m_height = height; 
  }
  if (width > 0) {
    m_width = width; 
  }
  try {
    m_grid.resize(height);
    for (int i = 0; i < height; i++) { 
      m_grid.at(i).resize(width); 
    }
  } 
  catch (exception &ex_rob) {
    cerr << "exception in Organism::Organism(): " << ex_rob.what() << endl;
  }
  fillWorld();
}

bool World::rangeCheck(const int row, const int column) {
  return row >= 0 && row < m_height && column >= 0 && column < m_width;
};

Organism *World::coupleOrganism(Organism *in_prob) {
  if (rangeCheck(in_prob->row(), in_prob->column())) {
    if (!organism(in_prob->row(), in_prob->column())) {
      m_grid.at(in_prob->row()).at(in_prob->column()) = in_prob;
      return in_prob;
    } else { return m_grid.at(in_prob->row()).at(in_prob->column()); };
  };
  return nullptr;
};

Organism *World::uncoupleOrganism(Organism *in_prob) {
  if (rangeCheck(in_prob->row(), in_prob->column())) {
    if (organism(in_prob->row(), in_prob->column())) {
      m_grid.at(in_prob->row()).at(in_prob->column()) = nullptr;
      return m_grid.at(in_prob->row()).at(in_prob->column());
    } 
    else { 
      return m_grid.at(in_prob->row()).at(in_prob->column()); 
    }
  }
  return m_grid.at(in_prob->row()).at(in_prob->column());
}

 // create Organism pointers and place in world randomly
int World::spawnOrganisms(const double density_kdf, const int generationLength_kii, const identity what_kii, const int intelligence_kii, const int tongueLength_kii, const int starvation_kii) {
 
  nanoSeed();
  int accum_ii = 0;
  while (accum_ii < density_kdf * m_width * m_height) { // infinite loop
    switch (what_kii) {
      case ORGANISM:
        break;
      case ANT:
        if (coupleOrganism(new Ant(rand() % m_height, rand() % m_width, generationLength_kii, this))) { 
          accum_ii++; 
        }
        break;
      case ANTEATER:
        switch (intelligence_kii) {
          case 0:
            if (coupleOrganism(new Anteater(rand() % m_height, rand() % m_width, generationLength_kii, this, tongueLength_kii, starvation_kii))) { 
              accum_ii++; 
            }
            break;
          case 1:
            if (coupleOrganism(new IntelligentAnteater(rand() % m_height, rand() % m_width, generationLength_kii, this, tongueLength_kii, starvation_kii))) { 
              accum_ii++; 
            }
            break;
        }
        break;
    }
     // if board is found to be completely full somehow
    if (countOrganisms() >= m_width * m_height) { 
      return accum_ii; 
    }
  }
  return accum_ii;
}

int World::countOrganisms(const int id_ii) const {
  int accum = 0;
  for (int i = 0; i < m_height; i++) {
    for (int j = 0; j < m_width; j++) {
      if (organism(i,j)) {
        if (id_ii == -1) { 
          accum++; 
        } 
        else { 
          accum += (organism(i, j)->is() == id_ii); 
        }
      }
    }
  }
  return accum;
}

void World::fillWorld(){
  for (int row = 0; row < height(); row++) {
		for (int column = 0; column < width(); column++) {
			m_grid[row][column] = nullptr;
		}
	}
}

vector<vector<Organism *> > World::index() {
  vector<vector<Organism *> > ret_veveprob;
  ret_veveprob.resize(IDENTITIES_QTY);
  for (int row = 0; row < m_height; row++) {
		for (int column = 0; column < m_width; column++) {
      if (m_grid.at(row).at(column)) {
        ret_veveprob.at(m_grid.at(row).at(column)->is()).push_back(m_grid.at(row).at(column));
      }
    }
  }
  return ret_veveprob;
}

//
int World::step() {
  m_age++;
  for (int i = 0; i < m_height; i++) {
    for (int j = 0; j < m_width; j++) {
      if (m_grid.at(i).at(j)) { 
        m_grid.at(i).at(j)->tick(); 
      }
    }
  }
  vector<vector<Organism *> > indexVec = index();
  for (Organism *val_prob : indexVec.at(ANTEATER)) { 
    val_prob->move(); 
  }
  indexVec = index();
  for (Organism *val_prob : indexVec.at(ANTEATER)) { 
    val_prob->feed(); 
  }
  indexVec = index();
  for (Organism *val_prob : indexVec.at(ANT)) { 
    val_prob->move(); 
  }
  indexVec = index();
  for (Organism *val_prob : indexVec.at(ANT)) {
    val_prob->checkReproduction(); 
  }
  indexVec = index();
  for (Organism *val_prob : indexVec.at(ANTEATER)) {
    val_prob->checkReproduction(); 
  }
  indexVec = index();
  for (Organism *val_prob : indexVec.at(ANTEATER)) {
    val_prob->checkHunger(); 
  }
  return m_age;
};

ostream &operator <<(ostream &ret_ros, const World &world) {
  ret_ros << "age of world: " << world.m_age << endl;
  ret_ros << "ants: " << world.countOrganisms(ANT) << endl;
  ret_ros << "anteaters: " << world.countOrganisms(ANTEATER) << endl << endl;
  for (int i = 0; i < 2 * world.m_width + 3; i++) { 
    ret_ros << "#"; 
  }
  ret_ros << endl;
  for (int row = 0; row < world.m_height; row++) {
    ret_ros << "# ";
		for (int column = 0; column < world.m_width; column++) {
			if (world.m_grid.at(row).at(column)) {
        switch (world.m_grid.at(row).at(column)->is()) {
          case ANT:
            ret_ros << 'a';
            break;
          case ANTEATER:
            ret_ros << (static_cast<Anteater *>(world.m_grid.at(row).at(column))->intelligence() ? 'I' : '@');
            break;
          default:
            break;
        }
      } else { 
          ret_ros << '-'; 
        };
      ret_ros << ' ';
		}
    ret_ros << "# " << row << endl;
	}
  for (int i = 0; i < 2 * world.m_width + 3; i++) { 
    ret_ros << "#"; 
  }
  return ret_ros;
}

World::~World() {
  for (int i = 0; i < m_grid.size(); i++) {
    for (int j = 0; j < m_grid.at(i).size(); j++) {
      if (organism(i, j)) {
        delete organism(i,j);
      }
    }
  }
}

#endif