#include "GameManager.h"

int main() {
    GameManager game(10, 10);
    game.init();

    while (game.isRunning()) {
        game.render();
        game.update();
    }

    cout << "\nGame Over!\n";
    return 0;
}