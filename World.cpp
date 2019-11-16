#ifndef _WORLD_CPP
#define _WORLD_CPP

#include <iostream>
#include "World.h"
#include "Ant.h"
#include "Anteater.h"
using namespace std;



World::World(int height_ii, int width_ii) {
  try {
    m_grid_veveprob.resize(height_ii);
    for (int i = 0; i < height_ii; i++) { m_grid_veveprob.at(i).resize(width_ii); };
  } catch (exception &ex_rob) {
    cerr << "exception in Organism::Organism(): " << ex_rob.what() << endl;
  };
  spawnAnts();
  spawnAnteaters();
  for (int row = 0; row < height_ii; row++) {
		m_grid_veveprob.push_back(vector<Organism *>(width_ii));
	}
};
void World::spawnAnts(){
  //create ant pointers and place in world randomly
}
void World::spawnAnteaters(){

}
void World::fillWorld(){
  for (int row = 0; row < height(); row++) {
		for (int column = 0; column < width(); column++) {
      // 
			m_grid_veveprob[row][column] = nullptr;
		}
	}
}

#endif