#include "Map.h"
#include "enemy.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Map::Map(int w, int h)
    : width(w), height(h),
    stairsX(-1), stairsY(-1), stairsVisible(false)
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

    stairsVisible = false;
}

bool Map::isInside(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool Map::canEnter(int x, int y) const {
    return isInside(x, y) && grid[y][x].isWalkable;
}

void Map::setStairs(int x, int y) {
    stairsX = x;
    stairsY = y;
}

void Map::showStairs(bool visible) {
    stairsVisible = visible;
}

bool Map::isStairsHere(int x, int y) const {
    return stairsVisible && x == stairsX && y == stairsY;
}

bool Map::stairsAreVisible() const {
    return stairsVisible;
}

void Map::show(int heroX, int heroY,
    const vector<Enemy*>& enemies,
    int chestX, int chestY,
    bool chestOpened) const
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            bool printed = false;

            if (x == heroX && y == heroY) {
                cout << 'H';
                printed = true;
            }

            for (auto e : enemies) {
                if (!printed &&
                    e->isAlive() &&
                    x == e->getX() &&
                    y == e->getY())
                {
                    cout << e->getSymbol();   // ← ПРАВИЛЬНО
                    printed = true;
                }
            }

            if (!printed && !chestOpened &&
                x == chestX && y == chestY)
            {
                cout << 'C';
                printed = true;
            }

            if (!printed && stairsVisible &&
                x == stairsX && y == stairsY)
            {
                cout << '>';
                printed = true;
            }

            if (!printed)
                cout << grid[y][x].symbol;
        }
        cout << "\n";
    }
}
