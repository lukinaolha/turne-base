#pragma once
#include <string>
#include "Entity.h" 
#include "Map.h"
using namespace std;

class Hero;

class Enemy : public Entity {
private:
    string name;     
    int health;            
    int aggroRange = 4;

public:
    Enemy(string n = "Goblin", int startX = 5, int startY = 2);

    virtual ~Enemy() = default;
    char getSymbol() const override { return 'E'; }
    bool isBlocking() const override { return true; }
    void update() override {}

    virtual void moveTowards(int heroX, int heroY, const Map& map);
    virtual void updateAI(int heroX, int heroY, const Map& map);
    void takeDamage();
    bool isAlive() const;        
    virtual void attackHero(Hero& hero);

    int getX() const { return x; }
    int getY() const { return y; }
};
class Goblin : public Enemy {
public:
    Goblin(int startX, int startY)
        : Enemy("Goblin", startX, startY) {
    }

    char getSymbol() const override { return 'G'; }

    void updateAI(int heroX, int heroY, const Map& map) override;
};

// ======= Orc: повільний, але сильніший =======
class Orc : public Enemy {
private:
    int moveCooldown = 0; // щоб рухався не на кожен хід

public:
    Orc(int startX, int startY)
        : Enemy("Orc", startX, startY) {
    }

    char getSymbol() const override { return 'O'; }

    void updateAI(int heroX, int heroY, const Map& map) override;
    void attackHero(Hero& hero) override;
};

// ======= Zombie: хаотичний =======
class Zombie : public Enemy {
public:
    Zombie(int startX, int startY)
        : Enemy("Zombie", startX, startY) {
    }

    char getSymbol() const override { return 'Z'; }

    void updateAI(int heroX, int heroY, const Map& map) override;
};