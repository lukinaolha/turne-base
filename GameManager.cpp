#include "GameManager.h"
#include "Move.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

GameManager::GameManager(int width, int height)
    : map(width, height),
    hero(nullptr),
    gameOver(false)
{
    srand((unsigned)time(0));
}

void GameManager::init() {

    map.generate(0, 0, 0, 0);

    int hx, hy;
    int ex, ey;
    do {
        hx = rand() % 10;
        hy = rand() % 10;
    } while (!map.canEnter(hx, hy));


    hero = new Hero("Player", 3, 1, hx, hy);
    
    hero->setMap(&map);

    for (int i = 0; i < 3; ++i) {
        do {
            ex = rand() % 10;
            ey = rand() % 10;
        } while (!map.canEnter(ex, ey) || (ex == hx && ey == hy));

        enemies.push_back(new Enemy("Goblin", ex, ey));
    }

    map.generate(hx, hy, ex, ey);


    (void)_getch();
}

void GameManager::render() {
    system("cls");

    map.show(hero->getX(), hero->getY(), enemies);
  
    hero->drawStatus();
}

void GameManager::update() {
    char input = _getch();

    Direction dir = Direction::None;
    switch (std::toupper(input)) {
    case 'W': dir = Direction::Up; break;
    case 'S': dir = Direction::Down; break;
    case 'A': dir = Direction::Left; break;
    case 'D': dir = Direction::Right; break;
    case 'Q':
        gameOver = true;
        return;
    default: break;
    }

    hero->move(dir, map);

    if (input == ' ' || input == '\r') {
        for (Enemy* enemy : enemies) {
            int dx = abs(hero->getX() - enemy->getX());

            int dy = abs(hero->getY() - enemy->getY());
            if (dx <= 1 && dy <= 1 && enemy->isAlive()) {
                enemy->takeDamage();
                (void)_getch();
                break;
            }
        }
    }
    bool allDead = true;
    for (Enemy* enemy : enemies) {
        if (enemy->isAlive()) {
            allDead = false;
            break;
        }
    }

    if (allDead) {
        gameOver = true;
    }
}

bool GameManager::isRunning() const {
    return !gameOver;
}
