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
    enemy(nullptr),
    gameOver(false)
{
    srand((unsigned)time(0));
}

void GameManager::init() {
    cout << "Initializing game...\n";

    map.generate(0, 0, 0, 0);

    int hx, hy;
    do {
        hx = rand() % 10;
        hy = rand() % 10;
    } while (!map.canEnter(hx, hy));

    int ex, ey;
    do {
        ex = rand() % 10;
        ey = rand() % 10;
    } while ((!map.canEnter(ex, ey)) || (ex == hx && ey == hy));

    map.generate(hx, hy, ex, ey);

    hero = new Hero("Player", 5, 1, hx, hy);
    
    hero->setMap(&map);

    enemy = new Enemy("Goblin", ex, ey);

    (void)_getch();
}

void GameManager::render() {
    system("cls");
    map.show(hero->getX(), hero->getY(), enemy->getX(), enemy->getY());
    cout << "\n";
    hero->drawStatus();
    cout << "\n(Use W/A/S/D to move, SPACE to attack, Q to quit)\n";
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
        int dx = abs(hero->getX() - enemy->getX());
        int dy = abs(hero->getY() - enemy->getY());
        if (dx <= 1 && dy <= 1 && enemy->isAlive()) {
            cout << "\nHero attacks enemy!\n";
            enemy->takeDamage();
            (void)_getch();
        }
    }

    if (!enemy->isAlive()) {
        cout << "\nEnemy defeated! You win!\n";
        gameOver = true;
    }
}   

bool GameManager::isRunning() const {
    return !gameOver;
}
