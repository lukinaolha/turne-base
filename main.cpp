#include "GameManager.h"
#include <cstdlib>
#include <ctime>

int main() {
    srand((unsigned int)time(nullptr));

    int hx = rand() % 10;
    int hy = rand() % 10;

    Hero hero("Player", 3, 1, hx, hy);

    GameManager game(10, 10, hero);
    game.init();

    while (game.isRunning()) {
        game.render();
        game.update();
    }
    return 0;
}
