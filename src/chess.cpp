#include "Game.h"

int main() {
    Game game;
    while (game.IsRunning()) {
        game.ExecuteFrame();
    }
    return 0;
}