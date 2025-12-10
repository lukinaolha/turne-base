#include "GameManager.h"
#include "AttackBuff.h"
#include "RangeBuff.h"
#include "HealthBuff.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

GameManager::GameManager(int width, int height, Hero& heroRef)
    : map(nullptr),
    hero(heroRef),
    chest(nullptr),
    gameOver(false),
    baseW(width),
    baseH(height)
{
    srand((unsigned)time(0));
    map = new Map(width, height);
}

GameManager::~GameManager() {
    delete map;
    for (auto e : enemies) delete e;
    delete chest;
}

bool GameManager::isEnemyAt(int x, int y) const {
    for (auto e : enemies)
        if (e->isAlive() && e->getX() == x && e->getY() == y)
            return true;
    return false;
}

void GameManager::spawnEnemies() {
    for (auto e : enemies) delete e;
    enemies.clear();

    int count = 3;

    for (int i = 0; i < count; ++i) {
        int ex, ey;

        do {
            ex = rand() % map->getWidth();
            ey = rand() % map->getHeight();
        } while (!map->canEnter(ex, ey) ||
            (ex == hero.getX() && ey == hero.getY()));

        int type = rand() % 3;

        if (type == 0) {
            enemies.push_back(new Goblin(ex, ey));
        }
        else if (type == 1) {
            enemies.push_back(new Orc(ex, ey));
        }
        else {
            enemies.push_back(new Zombie(ex, ey));
        }
    }
}

void GameManager::spawnChest() {
    int cx, cy;

    do {
        cx = rand() % map->getWidth();
        cy = rand() % map->getHeight();
    } while (!map->canEnter(cx, cy) ||
        (cx == hero.getX() && cy == hero.getY()));

    if (chest) delete chest;
    chest = new Chest(cx, cy);
}

void GameManager::regenerateLevel() {
  
    int newW = baseW + (rand() % 3 - 1);
    int newH = baseH + (rand() % 3 - 1);

    if (newW < 8) newW = 8;
    if (newW > 12) newW = 12;
    if (newH < 8) newH = 8;
    if (newH > 12) newH = 12;

    delete map;
    map = new Map(newW, newH);

    hero.clampToMap(*map);

    map->generate(hero.getX(), hero.getY(), -1, -1);

    spawnEnemies();
    spawnChest();

    int sx, sy;
    do {
        sx = rand() % map->getWidth();
        sy = rand() % map->getHeight();
    } while (!map->canEnter(sx, sy) ||
        (sx == hero.getX() && sy == hero.getY()));

    map->setStairs(sx, sy);
    map->showStairs(false);

    hero.setMap(map);
}

void GameManager::init() {
    regenerateLevel();
}

void GameManager::render() {
    system("cls");

    cout << "LEVEL: " << level
        << "    MAP: " << map->getWidth()
        << "x" << map->getHeight() << "\n";

    map->show(
        hero.getX(),
        hero.getY(),
        enemies,
        chest->getX(),
        chest->getY(),
        chest->isOpened()
    );

    hero.drawStatus();
}

void GameManager::update() {
    char input = _getch();
    Direction dir = Direction::None;

    switch (toupper(input)) {
    case 'W': dir = Direction::Up; break;
    case 'S': dir = Direction::Down; break;
    case 'A': dir = Direction::Left; break;
    case 'D': dir = Direction::Right; break;
    case 'Q': gameOver = true; return;
    default: break;
    }

    int oldHeroX = hero.getX();
    int oldHeroY = hero.getY();

    if (toupper(input) == 'F') {
        Enemy* e = findNearestEnemy();
        if (e)
            cout << "Nearest enemy: " << e->getSymbol()
            << " at (" << e->getX() << "," << e->getY() << ")\n";
        return;
    }

    if (toupper(input) == 'T') {
        sortEnemies();
        cout << "Enemies sorted by distance.\n";
        return;
    }

    if (toupper(input) == 'K') {
        saveGame();
        return;
    }

    if (toupper(input) == 'L') {
        loadGame();
        return;
    }

    hero.move(dir, *map, enemies);

    if (input == ' ' || input == '\r') {
        for (Enemy* enemy : enemies) {
            if (!enemy->isAlive()) continue;

            int dx = abs(oldHeroX - enemy->getX());
            int dy = abs(oldHeroY - enemy->getY());

            if (dx + dy == 1) {
                enemy->takeDamage();
                break;
            }
        }
    }

    if (chest &&
        !chest->isOpened() &&
        hero.getX() == chest->getX() &&
        hero.getY() == chest->getY())
    {
        string bonus = chest->open();

        if (bonus == "heal")
            hero.addBuff(new HealthBuff());
        else if (bonus == "attack")
            hero.addBuff(new AttackBuff());
        else if (bonus == "range")
            hero.addBuff(new RangeBuff());
    }

 
    for (Enemy* enemy : enemies) {

        if (!enemy->isAlive()) continue;

        int oldX = enemy->getX();
        int oldY = enemy->getY();

        enemy->updateAI(hero.getX(), hero.getY(), *map);

        int dx = abs(hero.getX() - oldX);
        int dy = abs(hero.getY() - oldY);

        if (enemy->isAlive() && dx + dy == 1) {
            enemy->attackHero(hero);

            if (!hero.isAlive()) {
                gameOver = true;
                return;
            }
        }
    }

    bool allDead = true;
    for (Enemy* e : enemies)
        if (e->isAlive()) { allDead = false; break; }

    if (allDead)
        map->showStairs(true);

    if (map->stairsAreVisible() &&
        hero.getX() == map->getStairsX() &&
        hero.getY() == map->getStairsY())
    {
        level++;
        regenerateLevel();
    }
}

bool GameManager::isRunning() const {
    return !gameOver;
}

Enemy* GameManager::findNearestEnemy() {
    Enemy* best = nullptr;
    int bestDist = 999999;

    for (auto e : enemies) {
        if (!e->isAlive()) continue;

        int dx = abs(hero.getX() - e->getX());
        int dy = abs(hero.getY() - e->getY());
        int dist = dx + dy;

        if (dist < bestDist) {
            bestDist = dist;
            best = e;
        }
    }

    return best;
}

void GameManager::sortEnemies() {
    sort(enemies.begin(), enemies.end(),
        [&](Enemy* a, Enemy* b) {
            int da = abs(hero.getX() - a->getX()) + abs(hero.getY() - a->getY());
            int db = abs(hero.getX() - b->getX()) + abs(hero.getY() - b->getY());
            return da < db;
        }
    );
}

void GameManager::saveGame() {
    ofstream file("save.txt");

    file << hero.getX() << " " << hero.getY() << "\n";
    file << enemies.size() << "\n";

    for (auto e : enemies) {
        file << e->getSymbol() << " "
            << e->getX() << " "
            << e->getY() << " "
            << e->isAlive() << "\n";
    }

    cout << "Game saved!\n";
}

void GameManager::loadGame() {
    ifstream file("save.txt");
    if (!file.is_open()) {
        cout << "No save file found!\n";
        return;
    }

    enemies.clear();

    int hx, hy;
    file >> hx >> hy;
    hero.setPosition(hx, hy);

    int count;
    file >> count;

    for (int i = 0; i < count; i++) {
        char type;
        int x, y, alive;
        file >> type >> x >> y >> alive;

        Enemy* e = nullptr;

        if (type == 'G') e = new Goblin(x, y);
        else if (type == 'O') e = new Orc(x, y);
        else if (type == 'Z') e = new Zombie(x, y);

        if (!alive) e->takeDamage();

        enemies.push_back(e);
    }

    cout << "Game loaded!\n";
}