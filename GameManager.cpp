#include "GameManager.h"
#include <iostream>
#include <conio.h>
using namespace std;

GameManager::GameManager(int width, int height)
    : map(width, height),
    gameOver(false) {
}

void GameManager::init() {
    cout << "Initializing game...\n";
    map.generate(hero.getX(), hero.getY(), enemy.getX(), enemy.getY());
}

void GameManager::render() {
    system("cls");  
    map.show(hero.getX(), hero.getY(), enemy.getX(), enemy.getY());
    cout << "\n";
    hero.drawStatus();
    cout << "\n(Use W/A/S/D to move, SPACE to attack, Q to quit)\n";
}

void GameManager::update() {
    char input = _getch();

    if (toupper(input) == 'Q') {
        gameOver = true;
        return;
    }

    bool moved = hero.move(input, map);

    if (input == ' ' || input == '\r') { 

        int dx = abs(hero.getX() - enemy.getX());
        int dy = abs(hero.getY() - enemy.getY());
        if (dx <= 1 && dy <= 1 && enemy.isAlive()) {
            cout << "\nHero attacks enemy!\n";
            enemy.takeDamage();
            _getch(); 
        }
    }

    if (!enemy.isAlive()) {
        cout << "\nEnemy defeated! You win!\n";
        gameOver = true;
    }
}

bool GameManager::isRunning() const {
    return !gameOver;
}
