#include "game_logic/GamePlay.h"
#include "game_logic/Player.h"
#include "interface/UserInterfaceConsole.h"
#include "game_logic/ChessBoard.h"
#include "app_logic/Enums.h"
#include "app_logic/Coord.h"

int main() {
    for (int i = 0; i < 2; i++) {
        std::string boardLayout;
        std::cin >> boardLayout;
        if (boardLayout == "normal") {
            ChessBoard cB(BoardLayouts::Normal);
            UserInterfaceConsole uI;
            uI.displayBoard(cB.getBoardView());
        } else if (boardLayout == "empty") {
            ChessBoard cB(BoardLayouts::Empty);
            UserInterfaceConsole uI;
            uI.displayBoard(cB.getBoardView());
        }
    }
    return 0;
}