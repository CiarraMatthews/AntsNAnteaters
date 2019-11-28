#ifndef _INTELLIGENT_ANTEATER_H
#define _INTELLIGENT_ANTEATER_H

#include "IntelligentAnteater.h"
#include "Anteater.h"

class IntelligentAnteater : public Anteater {
  public:
    // constructor:
    IntelligentAnteater();
    IntelligentAnteater(const int row_kii, const int col_kii, const int generationLength_kii, World *world_prob, const int tongueLength_kii, const int starvation_kii);
    // mutator:
    bool feed(int direction_ii) override;
    // accessor:
    identity is() const override { return ANTEATER; };
    int intelligence() const override { return 1; };
    // destructor:
    ~IntelligentAnteater();
};

#endif