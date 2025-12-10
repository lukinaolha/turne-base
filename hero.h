#pragma once
#include <string>
#include <vector>
#include "Buff.h"
#include "Move.h"
#include "Map.h"

class Enemy;
using namespace std;

class Hero {
private:
    string name;
    int health;
    int maxHealth;

    int attackRange;
    int attack;

    int x, y;
    Move moveController;
    Map* world;

    vector<Buff*> buffs;

public:
    Hero();
    Hero(string n, int hp, int range, int startX, int startY);

    void setMap(Map* mapNew) { world = mapNew; }

    bool move(Direction dir, const Map& map, const vector<Enemy*>& enemies);

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    bool isAlive() const { return health > 0; }

    void drawStatus() const;

    int getX() const { return x; }
    int getY() const { return y; }

    void setPosition(int newX, int newY) { x = newX; y = newY; }

    void clampToMap(const Map& map) {
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x >= map.getWidth())  x = map.getWidth() - 1;
        if (y >= map.getHeight()) y = map.getHeight() - 1;
    }

    void heal(int amount) {
        health += amount;
        if (health > maxHealth)
            health = maxHealth;
    }

    void increaseAttack(int amount) {
        attack += amount;
    }

    void increaseRange(int amount) {
        attackRange += amount;
    }

    int getAttack() const { return attack; }
    int getAttackRange() const { return attackRange; }

    void addBuff(Buff* b) {
        buffs.push_back(b);
    }

    int getTotalAttack() const {
        int bonus = 0;
        for (auto b : buffs) bonus += b->addAttack();
        return attack + bonus;
    }

    int getTotalRange() const {
        int bonus = 0;
        for (auto b : buffs) bonus += b->addRange();
        return attackRange + bonus;
    }

    int getTotalHealth() const {
        int bonus = 0;
        for (auto b : buffs) bonus += b->addHealth();
        return health + bonus;
    }
};
