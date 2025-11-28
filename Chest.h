#pragma once
#include <string>

class Chest {
private:
    int x, y;
    bool opened;

public:
    Chest(int x, int y) : x(x), y(y), opened(false) {}

    int getX() const { return x; }
    int getY() const { return y; }
    bool isOpened() const { return opened; }

    std::string open() {
        opened = true;

        int r = rand() % 3;  

        switch (r) {
        case 0: return "heal";
        case 1: return "attack";
        case 2: return "range";
        }

        return "none";
    }
};
