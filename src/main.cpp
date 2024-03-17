#include "game.h"

int main() {
    Game game;
    if (!game.init()) {
        printf("Failed to initialize the game!\n");
        return 1;
    }

    game.run();

    return 0;
}
//run the game