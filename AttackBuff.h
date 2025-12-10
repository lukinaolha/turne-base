#pragma once
#include "Buff.h"

class AttackBuff : public Buff {
public:
    int addAttack() const override { return 1; }
};