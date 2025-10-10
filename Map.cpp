#include "Map.h"
#include "hero.h"
#include "enemy.h"
#include <cstdlib>
#include <ctime>

Map::Map(int w, int h) : width(w), height(h) {
    grid.resize(height, vector<Cell>(width));
    srand((unsigned)time(0));
}

void Map::generate(int heroX, int heroY, int enemyX, int enemyY) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            if ((x == heroX && y == heroY) || (x == enemyX && y == enemyY)) {
                grid[y][x] = Cell('.', true, "floor");
                continue;
            }

            if (rand() % 10 == 0)
                grid[y][x] = Cell('#', false, "wall");
            else
                grid[y][x] = Cell('.', true, "floor");
        }
    }
}

bool Map::isInside(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool Map::canEnter(int x, int y) const {
    return isInside(x, y) && grid[y][x].isWalkable;
}

void Map::show(int heroX, int heroY, int enemyX, int enemyY) const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == heroX && y == heroY) cout << 'H';
            else if (x == enemyX && y == enemyY) cout << 'E';
            else cout << grid[y][x].symbol;
        }
        cout << '\n';
    }
}