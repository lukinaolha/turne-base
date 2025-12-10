#pragma once
#include "Buff.h"

class HealthBuff : public Buff {
public:
    int addHealth() const override { return 1; }
};