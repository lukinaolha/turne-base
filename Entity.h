#pragma once
#include <string>

class Entity {
protected:
    int x;
    int y;

public:
    Entity(int x, int y) : x(x), y(y) {}

    virtual char getSymbol() const = 0;
    virtual void update() = 0;
    virtual bool isBlocking() const = 0;

    virtual ~Entity() = default;

    int getX() const { return x; }
    int getY() const { return y; }
};
