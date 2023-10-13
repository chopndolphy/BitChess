#include "UserInterfaceConsole.h"
#include "Player.h"

ChessPiece* UserInterfaceConsole::getMoveChessPiece(const Player* player, ChessBoard* board) {
    Color playerColor = player->getColor();
    int x, y;
    if (playerColor == White) {
        std::cout << "White's turn. On which square is the piece you are moving? ";
    } else {
        std::cout << "Black's turn. On which square is the piece you are moving? ";
    }

    std::cin >> x >> y;

    return board->getPieceAt(Location(x,y));
}

Location UserInterfaceConsole::getMoveSquare(ChessBoard* board) {
    int x, y;

    std::cout << "And where is it moving to? ";
    std::cin >> x >> y;

    return Location(x,y);
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