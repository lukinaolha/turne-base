#pragma once
#include <string>
#include <vector>
using namespace std;

struct Cell {
    char symbol;
    bool isWalkable;
    string type;

    Cell(char s = '.', bool w = true, string t = "floor")
        : symbol(s), isWalkable(w), type(t) {
    }
};

class Enemy;

class Map {
private:
    int width, height;
    Cell** grid;

    int stairsX, stairsY;
    bool stairsVisible;

public:
    Map(int w, int h);
    ~Map();

    void generate(int hx, int hy, int ex, int ey);

    bool canEnter(int x, int y) const;
    bool isInside(int x, int y) const;

    void show(int heroX, int heroY,
        const vector<Enemy*>& enemies,
        int chestX, int chestY,
        bool chestOpened) const;

    void setStairs(int x, int y);
    void showStairs(bool visible);
    bool isStairsHere(int x, int y) const;
    bool stairsAreVisible() const;

    int getStairsX() const { return stairsX; }
    int getStairsY() const { return stairsY; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};
