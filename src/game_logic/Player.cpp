#include "game_logic/Player.h"
#include "game_logic/ChessPiece.h"
#include "interface/UserInterface.h"
#include "game_logic/ChessBoard.h"

Player::Player(Color color, ChessBoard* board, UserInterface* interface) {
    this->color = color;
    this->board = board;
    this->interface = interface;
}
void Player::makeMove() {
    Coord startCoord;
    Coord endCoord;
    while (!interface->getMove(color, startCoord, endCoord)) {
        ErrorLogger::relayError(ErrorCode::MOVE03, interface);
    }
    // does gameplay handle input conversion? do we create a coord for both start and dest? or do we directly get the piece and skip start coord?
    while (true) {
        if (board->getPieceAt(startCoord)->isLegalMove(endCoord)) { //Determines if chosen piece can move to chosen sqaure
            ErrorLogger::relayError(ErrorCode::MOVE01, interface);
        } else if (!board->kingIsProtected(board->getPieceAt(startCoord), endCoord)) { //Determines if move will put the player's own king into check.
            ErrorLogger::relayError(ErrorCode::MOVE02, interface);
        } else {
            break;
        }
        while (!interface->getMove(color, startCoord, endCoord)) {
            ErrorLogger::relayError(ErrorCode::MOVE03, interface);
        }
    }
    board->movePiece(startCoord, endCoord);
}