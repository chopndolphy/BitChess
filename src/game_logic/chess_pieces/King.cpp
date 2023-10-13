#include "King.h"
#include "ChessBoard.h"

King::King(Location square, Color pieceColor, ChessBoard* board) {
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
}

bool King::isLegalMove(Location square) {
    Location location = getLocation();

    int pathLengthX = std::abs(square.x - location.x);
    int pathLengthY = std::abs(square.y - location.y);
    if (square == location) {
        return false; // Moving to same square
    } else if (pieceBoard->canCastle(this, square)) {
        return true; // Castling
    } else if (pathLengthX > 1 || pathLengthY > 1) {
        return false; // Not moving one square
    } else if (square.x > 7 || square.x < 0 || square.y > 7 || square.y < 0) {
        return false; // Moving out of bounds
    } else if (pieceBoard->getPieceAt(square) && pieceBoard->getPieceAt(square)->getColor() != color) {
            return true; // Not moving to same colored piece
    }

    return false;
}
