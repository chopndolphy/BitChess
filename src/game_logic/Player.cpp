#include "Player.h"
Player::Player(Color color, ChessBoard* board, UserInterface* interface) {
    playerColor = color;
    playerBoard = board;
    playerInterface = interface;
}
void Player::makeMove() {
    ChessPiece* currentMovePiece {};
    Location currentMoveSquare {};

    do {
        currentMovePiece = playerInterface->getMoveChessPiece(this, playerBoard);
        if(currentMovePiece == nullptr){
            std::cout << "Invalid piece selected.\n";
            continue; // try again
        }

        currentMoveSquare = playerInterface->getMoveSquare(playerBoard);

        if (!currentMovePiece->isLegalMove(currentMoveSquare)) { //Determines if chosen piece can move to chosen sqaure
            ErrorLogger::relayError(MOVE01, playerInterface);
        } else if (!playerBoard->kingIsProtected(currentMovePiece, currentMoveSquare)) { //Determines if move will put the player's own king into check.
            ErrorLogger::relayError(MOVE02, playerInterface);
        } else {
            break;
        }

    } while(true);

    playerBoard->setPieceAt(currentMoveSquare, currentMovePiece);
}