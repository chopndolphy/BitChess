#include "forward.h"

#include "GamePlay.h"
#include "Player.h"
#include "UserInterfaceConsole.h"
#include "ChessBoard.h"
#include "Enums.h"

int main() {
    ViewType viewType = Console;
    if (viewType == Console) {
        ChessBoard cB;
        cB.printBoard();

        UserInterfaceConsole uI;
        Player w(White, &cB, &uI);
        Player b(Black, &cB, &uI);
        GamePlay game(&w, &b, &cB, &uI);
        while (!game.isGameOver()) {
            game.takeTurn();
        }
    }
    return 0;
}