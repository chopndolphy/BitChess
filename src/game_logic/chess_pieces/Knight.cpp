#include "Knight.h"
#include "ChessBoard.h"

Knight::Knight(Location square, Color pieceColor, ChessBoard* board) {
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
}

bool Knight::isLegalMove(Location square) {
    Location location = getLocation();

    int pathLengthX = std::abs(square.at(0) - location.at(0));
    int pathLengthY = std::abs(square.at(1) - location.at(1));
    if (square == location) {
        return false; // Moving to same square
    } else if (pieceBoard->getPieceAt(square) && pieceBoard->getPieceAt(square)->getColor() == color) {
        return false; // Moving to same colored piece
    } else if (location.at(0) > 7 || location.at(0) < 0 || location.at(1) > 7 || location.at(1) < 0) {
        return false; // Moving out of bounds
    } else if ((pathLengthX == 1 && pathLengthY == 2) || (pathLengthX == 2 && pathLengthY == 1)) {
        return true; // Correctly moving in L shape
    }

    return false;
}