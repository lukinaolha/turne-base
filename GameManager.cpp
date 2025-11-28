#include "GameManager.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
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

        if (bonus == "heal")        hero.heal(1);
        else if (bonus == "attack") hero.increaseAttack(1);
        else if (bonus == "range")  hero.increaseRange(1);
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
