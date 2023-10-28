#include "game_logic/Player.h"
#include "game_logic/ChessPiece.h"
#include "interface/UserInterface.h"
#include "game_logic/ChessBoard.h"

Player::Player(Color color, ChessBoard* board, UserInterface* interface) {
    playerColor = color;
    playerBoard = board;
    playerInterface = interface;
}
void Player::makeMove() {
    ChessPiece* currentMovePiece = playerInterface->getMoveChessPiece(this, playerBoard);
    std::vector<int> currentMoveSquare = playerInterface->getMoveSquare(playerBoard);
    while (true) {
        if (!currentMovePiece->isLegalMove(currentMoveSquare)) { //Determines if chosen piece can move to chosen sqaure
            ErrorLogger::relayError(MOVE01, playerInterface);
        } else if (!playerBoard->kingIsProtected(currentMovePiece, currentMoveSquare)) { //Determines if move will put the player's own king into check.
            ErrorLogger::relayError(MOVE02, playerInterface);
        } else {
            break;
        }
        currentMovePiece = playerInterface->getMoveChessPiece(this, playerBoard);
        currentMoveSquare = playerInterface->getMoveSquare(playerBoard);
    }
    currentMovePiece->move(currentMoveSquare);
}