#include "UserInterfaceConsole.h"
ChessPiece* UserInterfaceConsole::getMoveChessPiece(const Player* player, ChessBoard* board) {
    Color playerColor = player->getColor();
    int column;
    int row;
    std::vector<int> startSquare;
    if (playerColor = White) {
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