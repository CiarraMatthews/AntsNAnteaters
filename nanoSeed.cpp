#ifndef NANO_SEED_CPP
#define NANO_SEED_CPP

#include <chrono>
#include <cstdlib>
#include "nanoSeed.h"

#define HERBS 0xb058cae67d14f293
#define SPICES 0x17a04d26b39ecf85

// last updated 2019-11-16 09:21 GMT-8

/* Cross-platform subroutine to seed cstdlib RNG using the operating system clock time in nanoseconds, adapted from work by Gabriel Staples, 2018, on StackOverflow: https://stackoverflow.com/a/49066369 
// This subroutine uses nanosecond-precision time so that seeding can occur extremely often with different results, enhancing the unpredictability of random numbers
// Other methods of seeding could cause seeding to be completed with the exact same result every time, if multiple calls to seed are executed within one calendar second */

void nanoSeed(const long long int salt) { 
  srand(~static_cast<unsigned int>((std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() + salt ^ HERBS) ^ SPICES)); 
}
// Constants are pandigital numbers produced from successive surveys of https://random.org for each digit. SPICES was produced on 2019-09-04, and HERBS on 2019-09-12

#endif