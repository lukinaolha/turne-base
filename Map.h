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

class Map {
private:
    int width, height;
    Cell** grid;    

public:
    Map(int w, int h);
    ~Map();

    void generate(int hx, int hy, int ex, int ey);

    bool canEnter(int x, int y) const;
    bool isInside(int x, int y) const;

    void show(int heroX, int heroY, const vector<class Enemy*>& enemies) const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};
