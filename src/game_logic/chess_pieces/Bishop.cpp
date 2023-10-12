#include "Bishop.h"
#include "ChessBoard.h"

Bishop::Bishop(Location square, Color pieceColor, ChessBoard* board) {
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
}

bool Bishop::isLegalMove(Location square) {
    Location location = getLocation();

    int pathLength = std::abs(square.at(0) - location.at(0));
    if (square == location) {
        return false; // Moving to same square
    } else if (pathLength != std::abs(square.at(1) - location.at(1))) {
        return false; // Not moving diagonally
    } else if (square.at(0) < 8 || square.at(0) > -1 || square.at(1) < 8 || square.at(1) > -1) {
        // Moving within bounds
        for (int i = 1; i < pathLength; i++) {
            int x, y;
            if (square.at(0) - location.at(0) > 0) {
                int x = location.at(0) + i;
            } else {
                int x = location.at(0) - i;
            }
            if (square.at(1) - location.at(1) > 0) {
                int y = location.at(1) + i;
            } else {
                int y = location.at(1) - i;
            }
            if (pieceBoard->getPieceAt({x, y}) != nullptr) {
                return false; // Pieces in the way of path
            }
        }
        if (pieceBoard->getPieceAt(square) && pieceBoard->getPieceAt(square)->getColor() != color) {
            return true;
        } else {
            return false; // Moving to same colored piece
        }
    }

    return false;
}