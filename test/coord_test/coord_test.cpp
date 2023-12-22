#include "game_logic/GamePlay.h"
#include "game_logic/Player.h"
#include "interface/UserInterfaceConsole.h"
#include "game_logic/ChessBoard.h"
#include "app_logic/Enums.h"
#include "app_logic/Coord.h"

int main() {
    for (int i = 0; i < 5; i++) {
        char file;
        char rank;
        std::cin >> file >> rank;
        Coord coord(file, rank);
        std::cout << "x: " << coord.x() << std::endl;
        std::cout << "y: " << coord.y() << std::endl;
        std::cout << "file: " << coord.file() << std::endl;
        std::cout << "rank: " << coord.rank() << std::endl;
    }
    for (int i = 0; i < 5; i++) {
        int x;
        int y;
        std::cin >> x >> y;
        Coord coord(x, y);
        std::cout << "x: " << coord.x() << std::endl;
        std::cout << "y: " << coord.y() << std::endl;
        std::cout << "file: " << coord.file() << std::endl;
        std::cout << "rank: " << coord.rank() << std::endl;
    }
    return 0;
}