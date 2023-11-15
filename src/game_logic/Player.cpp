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
    std::string moveInput = playerInterface->getMove(playerColor);
    ChessPiece* targetPiece;
    Coord targetCoord;
    
    // does gameplay handle input conversion? do we create a coord for both start and dest? or do we directly get the piece and skip start coord?
    while (true) {
        if (!currentMovePiece->isLegalMove(currentMoveSquare)) { //Determines if chosen piece can move to chosen sqaure
            ErrorLogger::relayError(ErrorCode::MOVE01, playerInterface);
        } else if (!playerBoard->kingIsProtected(currentMovePiece, currentMoveSquare)) { //Determines if move will put the player's own king into check.
            ErrorLogger::relayError(ErorrCode::MOVE02, playerInterface);
        } else {
            break;
        }
        moveInput = playerInterface->getMove(playerColor);
    }
    currentMovePiece->move(currentMoveSquare);
}