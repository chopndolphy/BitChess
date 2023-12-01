#include "interface/UserInterfaceConsole.h"
#include "game_logic/ChessPiece.h"
#include "game_logic/Player.h"
#include "game_logic/ChessBoard.h"

bool UserInterfaceConsole::getMove(Color color, Coord &start, Coord &end) {
    std::string move;
    if (color == Color::White)
        std::cout << "White's move: ";
    else if (color == Color::Black)
        std::cout << "Black's move: ";
    std::cin >> move;
    start.setFile(move[0]);
    start.setRank(move[1]);
    end.setFile(move[2]);
    end.setRank(move[3]);
    return true; // TODO: Error checking!
}
void UserInterfaceConsole::displayError(std::string message) {
    std::cout << message << std::endl;
}
void UserInterfaceConsole::displayGameOver(GameState gameState) {
    switch (gameState) {
        case GameState::WhiteWins:
            std::cout << "GAME OVER: White wins!" << std::endl;
            break;
        case GameState::BlackWins:
            std::cout << "GAME OVER: White wins!" << std::endl;
            break;
        case GameState::Stalemate:
            std::cout << "GAME OVER: White wins!" << std::endl;
            break;
        default:
            std::cout << "INTERFACE ERROR: Unable to determine game over message." << std::endl;
    }
}
void UserInterfaceConsole::displayBoard(std::array<std::array<std::string, 8>, 8> boardView) {
    std::cout << "-------------------------" << std::endl;
    for (int i = 7; i > -1; i--) {
        for (int j = 0; j < 8; j++) {
            std::cout << "|" << boardView.at(i).at(j);
        }
        std::cout << "|" << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    
}