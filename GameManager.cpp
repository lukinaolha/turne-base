#include "GameManager.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
using namespace std;

GameManager::GameManager(int width, int height, Hero& heroRef)
    : map(nullptr),
    hero(heroRef),
    chest(nullptr),
    gameOver(false),
    baseW(width),
    baseH(height)
{
    map = new Map(width, height);
}

GameManager::~GameManager() {
    delete map;
    for (auto e : enemies) delete e;
    delete chest;
}

void GameManager::spawnEnemies() {
    for (auto e : enemies) delete e;
    enemies.clear();

    int count = 3; // постійно 3 вороги

    for (int i = 0; i < count; ++i) {
        int ex, ey;
        do {
            ex = rand() % map->getWidth();
            ey = rand() % map->getHeight();
        } while (!map->canEnter(ex, ey) ||
            (ex == hero.getX() && ey == hero.getY()));

        enemies.push_back(new Enemy("Goblin", ex, ey));
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
    // Невелика зміна розміру карти в межах [8;12]
    int newW = baseW + (rand() % 3 - 1); // baseW-1 .. baseW+1
    int newH = baseH + (rand() % 3 - 1);

    if (newW < 8) newW = 8;
    if (newW > 12) newW = 12;
    if (newH < 8) newH = 8;
    if (newH > 12) newH = 12;

    delete map;
    map = new Map(newW, newH);

    // гарантуємо, що герой всередині меж перед generate
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

    hero.move(dir, *map);

    if (chest &&
        !chest->isOpened() &&
        hero.getX() == chest->getX() &&
        hero.getY() == chest->getY())
    {
        string bonus = chest->open();

        if (bonus == "heal")   hero.heal(1);
        else if (bonus == "attack") hero.increaseAttack(1);
        else if (bonus == "range")  hero.increaseRange(1);

    }

    if (input == ' ' || input == '\r') {
        for (Enemy* enemy : enemies) {
            int dx = abs(hero.getX() - enemy->getX());
            int dy = abs(hero.getY() - enemy->getY());
            if (dx <= 1 && dy <= 1 && enemy->isAlive()) {
                enemy->takeDamage();
                break;
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
