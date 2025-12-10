#pragma once
#include "Buff.h"

class RangeBuff : public Buff {
public:
    int addRange() const override { return 1; }
};