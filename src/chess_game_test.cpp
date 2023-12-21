#include "game_logic/GamePlay.h"
#include "game_logic/Player.h"
#include "interface/UserInterfaceConsole.h"
#include "game_logic/ChessBoard.h"
#include "app_logic/Enums.h"
#include "app_logic/Coord.h"

int main() {
    Coord coord('A', '1');
    std::cout << "x:" << coord.x() << std::endl;
    std::cout << "y:" << coord.y() << std::endl;
    std::cout << "file:" << coord.file() << std::endl;
    std::cout << "rank:" << coord.rank() << std::endl;
    return 0;
}