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
    std::string moveInput = interface->getMove(color);
    ChessPiece* chosenPiece;
    Coord targetCoord;
    // does gameplay handle input conversion? do we create a coord for both start and dest? or do we directly get the piece and skip start coord?
    while (true) {
        if (!chosenPiece->isLegalMove(targetCoord)) { //Determines if chosen piece can move to chosen sqaure
            ErrorLogger::relayError(ErrorCode::MOVE01, interface);
        } else if (!board->kingIsProtected(chosenPiece, targetCoord)) { //Determines if move will put the player's own king into check.
            ErrorLogger::relayError(ErrorCode::MOVE02, interface);
        } else {
            break;
        }
        moveInput = interface->getMove(color);
    }
    chosenPiece->move(targetCoord);
}