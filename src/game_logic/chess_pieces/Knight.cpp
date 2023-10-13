#include "Knight.h"
#include "ChessBoard.h"

Knight::Knight(Location square, Color pieceColor, ChessBoard* board) {
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
}

bool Knight::isLegalMove(Location square) {
    Location location = getLocation();

    int pathLengthX = std::abs(square.x - location.x);
    int pathLengthY = std::abs(square.y - location.y);
    if (square == location) {
        return false; // Moving to same square
    } else if (pieceBoard->getPieceAt(square) && pieceBoard->getPieceAt(square)->getColor() == color) {
        return false; // Moving to same colored piece
    } else if (location.x > 7 || location.x < 0 || location.y > 7 || location.y < 0) {
        return false; // Moving out of bounds
    } else if ((pathLengthX == 1 && pathLengthY == 2) || (pathLengthX == 2 && pathLengthY == 1)) {
        return true; // Correctly moving in L shape
    }

    return false;
}