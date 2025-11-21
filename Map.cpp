#include "Map.h"
#include "enemy.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Map::Map(int w, int h) : width(w), height(h)
{
    grid = new Cell * [height];
    for (int y = 0; y < height; ++y)
        grid[y] = new Cell[width];
}

Map::~Map()
{
    for (int y = 0; y < height; ++y)
        delete[] grid[y];
    delete[] grid;
}

void Map::generate(int hx, int hy, int ex, int ey)
{
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
        {
            if (rand() % 10 == 0)
                grid[y][x] = Cell('#', false, "wall");
            else
                grid[y][x] = Cell('.', true, "floor");
        }

    grid[hy][hx] = Cell('.', true, "floor");
    if (ex >= 0 && ey >= 0)
        grid[ey][ex] = Cell('.', true, "floor");
}

bool Map::isInside(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool Map::canEnter(int x, int y) const {
    return isInside(x, y) && grid[y][x].isWalkable;
}

void Map::show(int heroX, int heroY, const vector<Enemy*>& enemies) const
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            bool printed = false;

            if (x == heroX && y == heroY) {
                cout << 'H';
                printed = true;
            }

            for (auto e : enemies) {
                if (!printed && e->isAlive() && x == e->getX() && y == e->getY()) {
                    cout << 'E';
                    printed = true;
                }
            }

            if (!printed)
                cout << grid[y][x].symbol;
        }
        cout << "\n";
    }
}
