#include "Game.h"

int main() {
    Game game;
    while (game.IsRunning()) {
        game.ExecuteFrame();
    }
    game.ShutDown();
    return 0;
}