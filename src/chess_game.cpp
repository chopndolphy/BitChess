#include "game_logic/GamePlay.h"
#include "game_logic/Player.h"
#include "interface/UserInterfaceConsole.h"
#include "game_logic/ChessBoard.h"
#include "app_logic/Enums.h"
#include "app_logic/Coord.h"

int main() {
    ViewType viewType = ViewType::Console;
    if (viewType == ViewType::Console) {
        ChessBoard cB;
        UserInterfaceConsole uI;
        Player w(Color::White, &cB, &uI);
        Player b(Color::Black, &cB, &uI);
        GamePlay game(&w, &b, &cB, &uI);
        while (!game.isGameOver()) {
            game.takeTurn();
        }
    }
    return 0;
}