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

const int g_DEFAULT_HEIGHT_ii = 30;
const int g_DEFAULT_WIDTH_ii = 30;
const int g_DEFAULT_TONGUE_LENGTH_ii = 5;
const int g_DEFAULT_STARVATION_ii = 3;
const double g_DEFAULT_ANT_DENSITY_df = 0.35;
const double g_DEFAULT_ANTEATER_DENSITY_df = 0.05;
const int g_ANT_GENERATION_ii = 3;
const int g_ANTEATER_GENERATION_ii = 8;

const int g_HEIGHT_LIMIT_ii = 50;
const int g_WIDTH_LIMIT_ii = 50;

World *worldBuilding() {
  int height_ii = -1, width_ii = -1;
  string intelligence_st = "z";
  cout << "Enter the height of the world to build: ";
  while (height_ii < 0 || height_ii > g_HEIGHT_LIMIT_ii) {
    cin >> height_ii;
    if (!cin) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); height_ii = -1; };
    if (height_ii < 0 || height_ii > g_HEIGHT_LIMIT_ii) {
      cout << "Please enter a positive integer not more than " << g_HEIGHT_LIMIT_ii << ": " << endl;
    };
  };
  cout << "Likewise for the width: ";
  while (width_ii < 0 || height_ii > g_WIDTH_LIMIT_ii) {
    cin >> width_ii;
    if (!cin) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); width_ii = -1; };
    if (width_ii < 0 || height_ii > g_HEIGHT_LIMIT_ii) {
      cout << "Please enter a positive integer not more than " << g_HEIGHT_LIMIT_ii << ": " << endl;
    };
  }; // !!! repetitive?
  World *ret_prob = new World(height_ii, width_ii);
  return ret_prob;
};

int intelligence() {
  char intelligence_st = 'z';
  cout << "Should the anteaters be intelligent? (y/n): ";
  cin >> intelligence_st;
  return toupper(intelligence_st) == 'Y';
};

int stepCounter() {
  static bool firstPrompt_bo = 1;
  string input_st = "";
  cout << "Enter a number of time steps to progress: ";
    if (firstPrompt_bo) {
      firstPrompt_bo = 0;
      cout << endl << "For a single step, just press Enter/Return." << endl;
      cout << "To quit the game, enter 0." << endl;
      cout << "Your choice: ";
    };
    getline(cin, input_st);
    if (input_st == "") { return 1; }
    else {
      try {
        while (stoi(input_st) < 0) {
          input_st = "-1";
          cout << "Please enter a positive integer: ";
        };
        return stoi(input_st);
      } catch (exception &ex_rob) {
        return 1;
      };
    };
};

int main(int argc, char **argv) {
  int iters_ii = -1;
  World *world_prob = worldBuilding();
  world_prob->spawnOrganisms(g_DEFAULT_ANT_DENSITY_df, g_ANT_GENERATION_ii, ANT);
  world_prob->spawnOrganisms(g_DEFAULT_ANTEATER_DENSITY_df, g_ANTEATER_GENERATION_ii, ANTEATER, intelligence(), g_DEFAULT_TONGUE_LENGTH_ii, g_DEFAULT_STARVATION_ii);
  cout << endl << *world_prob << endl;
  cin.ignore();
  while (1) {
    iters_ii = stepCounter();
    if (!iters_ii) {
      delete world_prob;
      return 0;
    } else {
      for (int i = 0; i < iters_ii; i++) {
        world_prob->step();
        cout << endl << *world_prob << endl << endl;
      };
    };
  };
};