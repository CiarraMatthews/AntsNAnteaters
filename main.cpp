/* Name: Alexandria González, Ciarra Matthews
// Course: CIS 25 #40712
// Lab #3
// Question 4
// This programme simulates the interaction of Ant and Anteater objects in a very simplified world. */

#include <iostream>
#include <limits>
#include <string>
#include "Ant.h"
#include "Anteater.h"
#include "Organism.h"
#include "World.h"

using namespace std;

//ANT CONSTANTS
const double DEFAULT_ANT_DENSITY = 0.35;
const int ANT_GENERATION = 3;

//ANTEATER CONSTANTS
const int DEFAULT_TONGUE_LENGTH = 5;
const int DEFAULT_STARVATION = 3;
const double DEFAULT_ANTEATER_DENSITY = 0.05;
const int ANTEATER_GENERATION = 8;

//WORLD CONSTANT
const int HEIGHT_AND_WIDTH_LIMIT = 50;

int getDimensions(int dimension){
  while (dimension < 0 || dimension > HEIGHT_AND_WIDTH_LIMIT) {
    cin >> dimension;
    if (!cin) {
      cin.clear(); 
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
      dimension = -1;
    }
    if (dimension < 0 || dimension > HEIGHT_AND_WIDTH_LIMIT) {
      cout << "Please enter a positive integer not more than " << HEIGHT_AND_WIDTH_LIMIT << ": " << endl;
    }
  }
  return dimension;
}

World *worldBuilding() {
  int height = -1, width = -1;
  cout << "Enter the height of the world to build: ";
  height = getDimensions(height);
  cout << "Likewise for the width: ";
  width = getDimensions(width);
 
  World *worldPtr = new World(height, width);
  return worldPtr;
}

//Gives user option to chose whether or not ants are intelligent
int intelligence() {
  char intelligence = 'z';
  cout << "Should the anteaters be intelligent? (y/n): ";
  cin >> intelligence;
  
  return toupper(intelligence) == 'Y';
}

//Allows user to chose how many world cycles to cycle through
int stepCounter() {
  static bool firstPrompt_bo = 1;
  string input = "";
  cout << "Enter a number of time steps to progress: ";
    if (firstPrompt_bo) {
      firstPrompt_bo = 0;
      cout << endl << "For a single step, just press Enter/Return." << endl;
      cout << "To quit the game, enter 0." << endl;
      cout << "Your choice: ";
    }
    getline(cin, input);
    if (input == "") { 
      return 1; 
    }
    else {
      try {
        while (stoi(input) < 0) {
          input = "-1";
          cout << "Please enter a positive integer: ";
        }
        return stoi(input);
      } catch (exception &ex_rob) {
        return 1;
      }
    }
}

int main(int argc, char **argv) {
  int iterations = -1;
  World *world = worldBuilding();
  world->spawnOrganisms(DEFAULT_ANT_DENSITY, ANT_GENERATION, ANT);
  world->spawnOrganisms(DEFAULT_ANTEATER_DENSITY, ANTEATER_GENERATION, ANTEATER, intelligence(), DEFAULT_TONGUE_LENGTH, DEFAULT_STARVATION);
  cout << endl << *world << endl;
  cin.ignore();
  while (1) {
    iterations = stepCounter();
    if (!iterations) {
      delete world;
      return 0;
    } 
    else {
      for (int i = 0; i < iterations; i++) {
        world->step();
        cout << endl << *world << endl << endl;
      }
    }
  }
}