#include "game_logic/King.h"

King::King(Color color, Coord location, ChessBoard* board) {
    this->location = location;
    this->color = color;
    this->board = board;
    movedYet = false;
    createView(color, PieceType::KingType);
}
bool King::isLegalMove(Coord destination) {
    int pathLengthX = std::abs(destination.x() - location.x());
    int pathLengthY = std::abs(destination.y() - location.y());
    if (location.x() == destination.x() && location.y() == destination.y()) {
        return false; // Moving to same square
    } else if (board->canCastle(this, destination)) {
        return true; // Castling
    } else if (pathLengthX > 1 || pathLengthY > 1) {
        return false; // Not moving one square
    } else if (destination.x() > 7 || destination.x() < 0 || destination.y() > 7 || destination.y() < 0) {
        return false; // Moving out of bounds
    } else if (board->getPieceAt(destination)->getColor() != color) {
            return true; // Not moving to same colored piece
    } else {
        return false;
    }
}
