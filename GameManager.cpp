#include "GameManager.h"
#include "Move.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

GameManager::GameManager(int width, int height, Hero& heroRef)
    : map(width, height),
    hero(heroRef),
    gameOver(false)
{
    srand((unsigned)time(0));
}

void GameManager::init()
{
    map.generate(hero.getX(), hero.getY(), -1, -1);

    int ex, ey;

    for (int i = 0; i < 3; ++i) {

        do {
            ex = rand() % 10;
            ey = rand() % 10;
        } while (!map.canEnter(ex, ey) ||
            (ex == hero.getX() && ey == hero.getY()));

        enemies.push_back(new Enemy("Goblin", ex, ey));
    }

    hero.setMap(&map);

}

void GameManager::render() {
    system("cls");

    map.show(hero.getX(), hero.getY(), enemies);
    hero.drawStatus();
}

void GameManager::update()
{
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

    hero.move(dir, map);

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
    for (Enemy* e : enemies) {
        if (e->isAlive()) {
            allDead = false;
            break;
        }
    }

    if (allDead)
        gameOver = true;
}

bool GameManager::isRunning() const {
    return !gameOver;
}
