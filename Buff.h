#pragma once

class Buff {
public:
    virtual ~Buff() {}

    virtual int addAttack() const { return 0; }
    virtual int addRange()  const { return 0; }
    virtual int addHealth() const { return 0; }
};