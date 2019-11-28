#ifndef _INTELLIGENT_ANTEATER_H
#define _INTELLIGENT_ANTEATER_H

#include "IntelligentAnteater.h"
#include "Anteater.h"

class IntelligentAnteater : public Anteater {
  public:
    // constructor:
    IntelligentAnteater();
    IntelligentAnteater(const int row, const int column, const int generationLength, World *world, const int tongueLength, const int starvation);
    // mutator:
    bool feed(int direction) override;
    // accessor:
    identity is() const override { return ANTEATER; }
    int intelligence() const override { return 1; }
    // destructor:
    ~IntelligentAnteater();
};

#endif