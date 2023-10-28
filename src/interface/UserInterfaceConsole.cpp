#include "interface/UserInterfaceConsole.h"
#include "game_logic/ChessPiece.h"
#include "game_logic/Player.h"
#include "game_logic/ChessBoard.h"

ChessPiece* UserInterfaceConsole::getMoveChessPiece(const Player* player, ChessBoard* board) {
    Color playerColor = player->getColor();
    int column;
    int row;
    std::vector<int> startSquare;
    if (playerColor == White) {
        std::cout << "White's turn. On which square is the piece you are moving? ";
    } else {
        std::cout << "Black's turn. On which square is the piece you are moving? ";
    }
    std::cin >> column >> row;
    startSquare.push_back(column);
    startSquare.push_back(row);
    return board->getPieceAt(startSquare);
}
std::vector<int> UserInterfaceConsole::getMoveSquare(ChessBoard* board) {
    int column;
    int row;
    std::vector<int> endSquare;
    std::cout << "And where is it moving to? ";
    std::cin >> column >> row;
    endSquare.push_back(column);
    endSquare.push_back(row);
    return endSquare;
}
void UserInterfaceConsole::displayError(std::string message) {
    std::cout << message << std::endl;
}
void UserInterfaceConsole::displayGameOver(GameState gameState) {
    switch (gameState) {
        case WhiteWins:
            std::cout << "GAME OVER: White wins!" << std::endl;
            break;
        case BlackWins:
            std::cout << "GAME OVER: White wins!" << std::endl;
            break;
        case Stalemate:
            std::cout << "GAME OVER: White wins!" << std::endl;
            break;
        default:
            std::cout << "INTERFACE ERROR: Unable to determine game over message." << std::endl;
    }
}