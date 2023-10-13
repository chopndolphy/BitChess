#include "Bishop.h"
#include "ChessBoard.h"

Bishop::Bishop(Location square, Color pieceColor, ChessBoard* board) {
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
}

bool Bishop::isLegalMove(Location square) {
    Location location = getLocation();

    int pathLength = std::abs(square.x - location.x);
    if (square == location) {
        return false; // Moving to same square
    } else if (pathLength != std::abs(square.y - location.y)) {
        return false; // Not moving diagonally
    } else if (square.x < 8 || square.x > -1 || square.y < 8 || square.y > -1) {
        // Moving within bounds
        for (int i = 1; i < pathLength; i++) {
            int x, y;
            if (square.x - location.x > 0) {
                int x = location.x + i;
            } else {
                int x = location.x - i;
            }
            if (square.y - location.y > 0) {
                int y = location.y + i;
            } else {
                int y = location.y - i;
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