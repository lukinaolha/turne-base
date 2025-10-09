#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Map {
private:
    struct Cell {
        char symbol;
        bool isWalkable;
        string type;

        Cell(char s = '.', bool walk = true, string t = "floor")
            : symbol(s), isWalkable(walk), type(t) {
        }
    };

    int width, height;
    vector<vector<Cell>> grid;

public:
    Map(int w = 10, int h = 10);
    void generate();                                    
    void show(int heroX, int heroY, int enemyX, int enemyY) const; 
    bool canEnter(int x, int y) const;                   
    bool isInside(int x, int y) const;
};
